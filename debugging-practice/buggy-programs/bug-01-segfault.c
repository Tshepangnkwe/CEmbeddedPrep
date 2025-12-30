#include &lt;stdio.h&gt;

int main() {
    int *ptr = NULL;
    *ptr = 42;  // Segmentation fault
    return 0;
}