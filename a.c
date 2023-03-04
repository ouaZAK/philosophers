void blabla(int *****nb)
{

	*****nb = 42;

}
int main()
{
	int x = 100;
	int *a;
	int **b; 
	int ***c;
	int ****d;
	int *****e;

	a = &x;
	b = &a;
	c = &b;
	d = &c;
	e = &d;
	printf("x ==> %d\n", *****e); 
}

