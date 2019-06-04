#ifndef GETCH_H
#define GETCH_H


/*
Provides a function for capturing unbuffered user input, I.e.
real-time user input. Each call to getch() will wait until the
user presses a key, then return that character. That key will not
be echoed to the terminal, and the cursor will not move.
*/

/*
char getch() {
    char buf = 0;
    struct termios old = {0};
    if (tcgetattr(0, &old) < 0)
            perror("tcsetattr()");
    old.c_lflag &= ~ICANON;
    old.c_lflag &= ~ECHO;
    old.c_cc[VMIN] = 1;
    old.c_cc[VTIME] = 0;
    if (tcsetattr(0, TCSANOW, &old) < 0)
            perror("tcsetattr ICANON");
    //if (read(0, &buf, 1) < 0)
    //        perror ("read()");
    old.c_lflag |= ICANON;
    old.c_lflag |= ECHO;
    if (tcsetattr(0, TCSADRAIN, &old) < 0)
            perror ("tcsetattr ~ICANON");
    return (buf);
}
 */

#endif /* GETCH_H */

