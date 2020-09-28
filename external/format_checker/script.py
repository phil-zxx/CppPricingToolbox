import glob

if __name__ == '__main__':
    arr =  [file_name for ext in ['**.hpp', '**.cpp','**.py','**CMakeLists.txt'] for file_name in glob.glob('**/'+ext, recursive=True) if file_name[0:8] != 'external']
    for file_name in arr:
        write_new_file = False
        with open(file_name, 'r') as f:
            content = f.read()

        if content[-1] != '\n':
            write_new_file = True
            content += '\n'

        if ' \n' in content:
            write_new_file = True
            while ' \n' in content:
                content = content.replace(' \n', '\n')

        if file_name[-3:] == 'hpp':
            if content[0:13] != '#pragma once\n':
                print('ERROR: No "#pragma once" present:', file_name)

            for pattern, msg in [['if(', 'Need space between IF and bracket'],
                                 ['if constexpr(', 'Need space between IF constexpr and bracket'],
                                 ['while(', 'Need space between WHILE and bracket'],
                                 ['switch(', 'Need space between SWITCH and bracket'],
                                 ['){', 'Need space between ) and {']]:
                if pattern in content:
                    for i, line in enumerate(content.split('\n')):
                        if pattern in line:
                            print('ERROR:  '+msg+': '+file_name+'  (line '+str(i+1)+')')

        if write_new_file:
            with open(file_name, 'w') as f:
                f.write(content)
