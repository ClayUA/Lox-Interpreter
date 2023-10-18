class Lox {
    main(int argc, char* argv[]) {
        if (argc > 1) {
            cout << "Usage: jlox [script]" << endl;
            exit(1); 
    } else if (argc == 1) {
        runFile(argv[0]);
    } else {
        runPrompt();
    }
  }
}