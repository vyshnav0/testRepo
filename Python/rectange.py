class Rectangle:
    def __init__(self,l,b):
        self.l = l
        self.b = b

    def area(self):
        return self.l*self.b

def main():
    r1 = Rectangle(3,4)
    r2 = Rectangle(43,56)
    print("Area of 1st rectange is: ",r1.area()," and that of 2nd rectange is: ",r2.area())

main()