int foo(){
return 0;
}


int world(){
    return 0;
}
int hello(){
    world();
    hello();
    hello();
    return 0;
}



int main(){
int a=foo();
hello();
return a;
}


