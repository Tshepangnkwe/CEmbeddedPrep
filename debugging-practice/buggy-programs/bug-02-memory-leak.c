#include &lt;stdio.h&gt;
#include &lt;stdlib.h&gt;

int main() {
    int *ptr = malloc(sizeof(int) * 10);
    // Forgot to free ptr - memory leak
    return 0;
}