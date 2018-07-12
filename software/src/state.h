class State {
    public:
        virtual void on_start() = 0;
        virtual void on_loop() = 0;
        virtual void on_end() = 0;
};