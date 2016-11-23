#ifndef COMPUTE_H_
# define COMPUTE_H_
int compile_worker(void);
int create_worker(int n);
void	read_worker(int n, long int *path_ok, long int *path_ko);
#endif
