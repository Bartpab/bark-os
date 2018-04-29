extern void scrollup(unsigned int);
extern void print(char *);

extern char kY;
extern char kattr;

void _start(void)
{
        kY = 18;
        kattr = 0x5E;
        print("un message\n");

        kattr = 0x4E;
        print("un autre message\n");

        scrollup(40);

        while (1);
}