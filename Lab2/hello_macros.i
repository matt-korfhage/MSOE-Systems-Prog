# 0 "hello.c"
# 0 "<built-in>"
# 0 "<command-line>"
# 1 "/usr/include/stdc-predef.h" 1 3 4
# 0 "<command-line>" 2
# 1 "hello.c"



int main(int argc, char* argv[])
{
    int array1[10];
    int array2[10];

    for(int i = 0; i < 10; i++)
    {

        array1[i] = i;


        array2[i] = i / 2;
    }
}
