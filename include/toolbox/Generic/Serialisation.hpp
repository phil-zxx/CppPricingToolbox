#pragma once

#include <fstream>
#include <cstddef>
#include <vector>
#include <array>
#include <string>
#include <map>
#include <unordered_map>
#include <memory>
#include <optional>
#include <variant>
#include <cstring>


namespace Toolbox
{
    struct SampleData
    {
        SampleData(double a, std::string b, std::vector<int> c)
            : a(a), b(b), c(c) { }

        double a;
        std::string b;
        std::vector<int> c;
    };

    template<class... Args>
    struct false_template : std::false_type { };

    template<class T>
    using remove_cv_ref_t = typename std::remove_cv_t<typename std::remove_reference_t<T>>;

    template<class, class = void> struct has_begin : std::false_type { };
    template<class T> struct has_begin<T, std::void_t<decltype(*std::begin(std::declval<T>()))>> : std::true_type { };
    template<class T> constexpr bool has_begin_v = has_begin<T>::value;

    template <class T, template <class...> class Template> constexpr bool is_instance_of_v = false;
    template <template <class...> class Template, class... Args> constexpr bool is_instance_of_v<Template<Args...>, Template> = true;

    template<class T> constexpr bool is_std_optional_v  = is_instance_of_v<T, std::optional>;
    template<class T> constexpr bool is_std_tuple_v     = is_instance_of_v<T, std::tuple> || is_instance_of_v<T, std::pair>;
    template<class T> constexpr bool is_std_map_v       = is_instance_of_v<T, std::map> || is_instance_of_v<T, std::unordered_map>;
    template<class T> constexpr bool is_std_smart_ptr_v = is_instance_of_v<T, std::shared_ptr> || is_instance_of_v<T, std::unique_ptr>;


    class ByteArchive
    {
    private:
        template<std::size_t...Is, class V>
        auto storeVariant(const V& obj, std::index_sequence<Is...>)
        {
            store(obj.index());
            ([&]() {
                if (Is == obj.index())
                    store(std::get<Is>(obj)); }(), ...);
        }

        template<std::size_t...Is, class V>
        auto loadVariant(V& obj, std::index_sequence<Is...>)
        {
            const auto index = load<size_t>();
            ([&]() {
                if (Is == index)
                    obj = load<remove_cv_ref_t<decltype(std::get<Is>(obj))>>(); }(), ...);
        }

    public:
        template <class... _Types>
        void store(const std::variant<_Types...>& obj)
        {
            storeVariant(obj, std::make_index_sequence<sizeof...(_Types)>{});
        }

        template <class... _Types>
        void load(std::variant<_Types...>& obj)
        {
            loadVariant(obj, std::make_index_sequence<sizeof...(_Types)>{});
        }

        template <class T>
        void store(const T& obj)
        {
            if constexpr (std::is_pointer_v<T> || is_std_optional_v<T>)
            {
                store(static_cast<bool>(obj));
                if (obj)
                    store(*obj);
            }
            else if constexpr (std::is_floating_point_v<T> || std::is_trivial_v<T>)
            {
                const size_t sizeT = sizeof(T);
                if (m_writePos + sizeT > m_bytes.size())
                    m_bytes.resize((m_writePos + sizeT) * 2);

                std::memcpy(m_bytes.data() + m_writePos, std::addressof(obj), sizeT);
                m_writePos += sizeT;
            }
            else if constexpr (has_begin_v<T>)
            {
                store(std::size(obj));
                for (const auto& element : obj)
                    store(element);
            }
            else if constexpr (is_std_tuple_v<T>)
            {
                std::apply([&](auto&&... val) { (store(val), ...); }, obj);
            }
            else if constexpr (std::is_same_v<T, SampleData>)
            {
                store(obj.a, obj.b, obj.c);
            }
            else if constexpr (is_std_smart_ptr_v<T>)
            {
                store(obj.get());
            }
            else
            {
                static_assert(false_template<T>::value, "Provided Template argument is not covered in save function");
            }
        }

        template<class... Ts>
        void store(const Ts&... val)
        {
            (store(val), ...);
        }

        template<class T>
        void load(T& obj)
        {
            if (m_readPos >= m_writePos)
                throw std::out_of_range("Read position has gone beyond internal storage length");

            if constexpr (std::is_floating_point_v<T> || std::is_trivial_v<T>)
            {
                const size_t sizeT = sizeof(T);
                std::memcpy(&obj, m_bytes.data() + m_readPos, sizeT);
                m_readPos += sizeT;
            }
            else if constexpr (is_std_map_v<T>)
            {
                const size_t size = load<size_t>();

                for (size_t i = 0; i < size; ++i)
                {
                    auto key = load<typename T::key_type>();
                    obj[std::move(key)] = load<typename T::mapped_type>();
                }
            }
            else if constexpr (has_begin_v<T>)
            {
                const size_t size = load<size_t>();
                obj.reserve(size);

                for (size_t i = 0; i < size; ++i)
                    obj.insert(obj.end(), load<typename T::value_type>());
            }
            else if constexpr (is_std_tuple_v<T>)
            {
                std::apply([&](auto&& ... val) {(load(val), ...); }, obj);
            }
            else if constexpr (is_std_smart_ptr_v<T>)
            {
                obj = std::move(T(load<typename T::element_type*>()));
            }
            else if constexpr (is_std_optional_v<T>)
            {
                if (load<bool>())
                    obj = load<typename T::value_type>();
            }
            else
            {
                static_assert(false_template<T>::value, "Provided Template argument is not covered in load function");
            }
        }

        template<class... Ts>
        std::tuple<Ts...> loadTuple()
        {
            std::tuple<Ts...> obj;
            std::apply([&](auto&&... val) { (load(val), ...); }, obj);
            return obj;
        }

        template<class T>
        T load()
        {
            using Tclean = remove_cv_ref_t<std::remove_pointer_t<T>>;

            if constexpr (std::is_pointer_v<T>)
            {
                if (load<bool>())
                {
                    if constexpr (std::is_default_constructible_v<Tclean>)
                    {
                        auto obj = new Tclean();
                        load(*obj);
                        return obj;
                    }
                    else
                    {
                        return new Tclean(load<Tclean>());
                    }
                }
                return nullptr;
            }
            else if constexpr (std::is_default_constructible_v<Tclean>)
            {
                Tclean obj{};
                load(obj);
                return obj;
            }
            else if constexpr (std::is_same_v<Tclean, SampleData>)
            {
                return std::make_from_tuple<SampleData>(loadTuple<double, std::string, std::vector<int>>());
            }
            else
            {
                static_assert(false_template<T>::value, "Provided Template argument is not covered in load function");
            }
        }

        void saveToFile(const std::string& fileName)
        {
            std::ofstream outFile(fileName, std::ios::out | std::ios::binary);
            outFile.write(reinterpret_cast<const char*>(m_bytes.data()), m_writePos);
            outFile.close();
        }

        void loadFromFile(const std::string& fileName)
        {
            std::basic_ifstream<std::byte> inFile(fileName, std::ios::binary);

            m_bytes.clear();
            m_bytes   = std::vector<std::byte>(std::istreambuf_iterator<std::byte>(inFile), {});
            m_readPos = m_bytes.size();
            m_readPos = 0;

            inFile.close();
        }

    private:
        std::vector<std::byte> m_bytes;
        size_t m_writePos = 0, m_readPos = 0;
    };
}
