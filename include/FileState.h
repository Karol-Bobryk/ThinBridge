#ifndef FILE_STATE_H
#define FILE_STATE_H

#include <stdbool.h>
#include <stddef.h>

typedef struct {
  char **source_filenames;
  size_t source_filenames_count;

  char **destination_filenames;
  size_t destination_filenames_count;

  int desynchronized_count;

  char **deleted_files;
  size_t deleted_files_count;

  char **created_files;
  size_t created_files_count;

  char **modified_files;
  size_t modified_files_count;
} FileState;

// przyjmuje sciezki i flage rekurencjii
FileState *file_state_init(const char *source_path,
                           const char *destination_path, bool recursive);

void file_state_free(FileState *file_state);

void scan_directory(const char *base_path, char ***list, size_t *count,
                    char *PATH_TYPE, bool recursive);

int file_state_append_to_list(char ***list, size_t *list_count, char *elem);

// Return value:
// Returns false when date differs. Returns true otherwise.
bool file_state_compare_last_modified(char *file_a, char *file_b);

char *file_state_join_paths(char *buf, size_t buf_size, char *start_path,
                            char *end_path);

// Return value:
// Returns false when files differ. Returns true otherwise.
bool file_state_compare_lists(FileState *file_state);

// sprawdzanie czy sciezka to katalog
bool is_directory(const char *path);

int file_state_delete(char *path);

int file_state_empty_dir(char *path);

void file_state_correct_dst(FileState *file_state);

int file_state_remove_from_list(char ***list, size_t *list_count);

#endif // FILE_STATE_H
