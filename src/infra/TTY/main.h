class TTY {
    public:
        /// FuncToRunInTTY must write anything into tty
        void runInTTY(void (*FuncToRunInTTY)(TTY&));
        
    private:
        static void OpenTTY();
        static void CloseTTY();
        
};
