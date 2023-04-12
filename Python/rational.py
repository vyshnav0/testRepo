class Rational(object):
    def __init__(self,numer,denom):
        self.numer = numer
        self.denom = denom
        self.reduce()

    def numerator(self):
        return f"The numerator of {self} is {self.numer}"

    def denominator(self):
        return f"The denominator of {self} is {self.denom}"

    def __str__(self):
        return (str(self.numer) + "/" + str(self.denom))

    def  reduce(self):
        div = self.gcd(self.numer,self.denom)
        self.numer = self.numer//div
        self.denom = self.denom//div

    def gcd(self,a,b):
        if(b==0):
            return a
        else:
            return self.gcd(b,a%b)
    
    def __add__(self,other):
        newNumer = self.numer*other.denom + other.numer*self.denom
        newDenom = self.denom * other.denom
        return Rational(newNumer,newDenom)
    
    def __sub__(self,other):
        newNumer = self.numer*other.denom - other.numer*self.denom
        newDenom = self.denom * other.denom
        return Rational(newNumer,newDenom)
    
    def __mul__(self,other):
        newNumer = self.numer*other.numer
        newDenom = self.denom*other.denom
        return Rational(newNumer,newDenom)
    
    def __truediv__(self,other):
        newNumer = self.numer*other.denom
        newDenom = self.denom*other.numer
        return Rational(newNumer,newDenom)
    
    def __lt__(self,other):
        num1 = self.numer*other.denom
        num2 = self.denom*other.numer
        if(num1<num2):
            return "True"
        elif(num1==num2):
            return "Equal"
        else:
            return "False"
        
def main():
    r1 = Rational(3,5)
    r2 = Rational(14,19)
    print(r2)
    print(r1 + r2)
    print(r1 - r2)
    print(r1 * r2)
    print(r1 / r2)
    print(r1 < r2)

main()