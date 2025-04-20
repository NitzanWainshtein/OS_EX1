//
// Created by nitzan on 4/12/25.
//

int main() {
    int *pointer = (int *) 0xdeadbeef;
    *pointer = 2;
    return 0;
}
