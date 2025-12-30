#include &lt;stdio.h&gt;

int main() {
    int x = 5;
    if (x = 10) {  // Logic error: assignment instead of comparison
        printf("x is 10\n");
    }
    return 0;
}