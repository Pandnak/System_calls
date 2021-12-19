enum {
    RESULT_OK = 0,
    RESULT_BAD_ARG,
    RESULT_BAD_FILE_TYPE,
    RESULT_OPEN_FAILED, 
    RESULT_BAD_READ,
    RESULT_BAD_WRITE,
    RESULT_BAD_CLOSE,
    RESULT_BAD_STAT,
    RESULT_BAD_FILE_DELETE,
    RESULT_BAD_COPY_TIME,
    RESULT_BAD_READLINK,
    RESULT_ERR,
    NOT_DIR,
    SUITABLE_DIR
};

const char* typeFile(const mode_t mode);

int rm_file(const char* filename);

void print_access(const struct stat *sb);

ssize_t writeall(int fd, const void *buf, size_t count);

void printf_time(const time_t *tmp);

int my_copy_files(unsigned source_fd, unsigned dest_fd, const char* dest_name, long long size_source, const unsigned max_len);
