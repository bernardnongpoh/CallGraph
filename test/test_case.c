void DC(){}
void BC(){
DC();
}

void C();
void F( ) { }
void E( ) { }
void D( ) { }
void C( ) { D( ) ; E( ) ; }
void B( ) { C( ) ; }
void A( ) { B( ) ; }
int main ( ) {
void (* p) ( ) ;
A( );
p = &C;
(*p)( ) ;
struct s{
void (* q) ( ) ;
int value;
} s1;
s1.q = &F;
s1.q();

void (*q)();
int a=10;
if(a>10){
    q=&F;
}
else{
    q=&E;

}
(*q)();
}
