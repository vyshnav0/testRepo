class Circle:
    pi = 22/7
    def __init__(self,radius):
        self.radius = radius

    def area(self):
        return self.pi*(self.radius**2)
    
    def circumference(self):
        return 2*self.pi*self.radius
    
    def __str__(self):
        return "Circle with radius ",self.radius
    
def main():
    c1 = Circle(5)
    c2 = Circle(19)
    print("Area of ",c1," is ",c1.area()," and its circumference is ",c1.circumference())
    print("Area of ",c2," is ",c2.area()," and its circumference is ",c2.circumference())

main()