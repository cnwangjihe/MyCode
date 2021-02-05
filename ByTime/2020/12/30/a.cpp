class ClassSealer {
protected:
  ClassSealer(){}
};
class Sealed : private ClassSealer
{
   // ...
};
class FailsToDerive : public Sealed
{
   // Cannot be instantiated
};

int main()
{
	FailsToDerive a;
	return 0;
}