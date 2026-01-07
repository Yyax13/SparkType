class TTY {
    static const char *user;
    static const char *pass;
    public:
        /// FuncToRunInTTY must write anything into tty
        void runInTTY(void (*FuncToRunInTTY)(TTY&));
        
    private:
        static void OpenTTY();
        static void CloseTTY();
        
};

extern TTY tty;
