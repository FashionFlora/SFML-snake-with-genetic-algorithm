import sys

if len(sys.argv) < 3:
    print('command format: extract.py filename name_of_output_files')
    print(' any \'#\' in name_of_output_files will be replaced with the generation number')
    sys.exit()

file = open(sys.argv[1], 'r')
filename = sys.argv[2]
gen = 1
for line in file:
    weights = line.split('|')[-1].split(' ')
    savefile = open(filename.replace('#', str(gen)), 'w')
    for weight in weights:
        if weight != '' or weight != '\n':
            savefile.write(weight + ' ')
    gen += 1

