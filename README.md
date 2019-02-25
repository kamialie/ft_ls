# ft_ls

## Reprogramming of terminal ls command

Supported flags:
- A - list all entries except . and ..
- C - force multi-column output
- G - enable colorized output
- R - recursively list subdirectories
- a - include directory entries whos names begins with a dot (.)
- f - output is not sorted; a flag is turned on
- g - do not show user name in long format (group name in long format)
- l - list in long format
- r - reverse the order of the current sort
- t - sort by time modified
- u - sort by time of last access
- x - multicolumn format with entries sorted across, rather than down
- 1 - force output to be one entry per line

### Usage

compile the project with make command

run ./ft_ls with any supported flags like you would do with familiar ls command

### Project commands

make - compile executable

make clean - remove object files

make fclean - make clean plus remove library and executable

make re - remove all temporary files and compile the project again
