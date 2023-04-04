from functools import reduce

class classroom:
    def __init__(self,name,roll,num):
        self.name = name
        self.roll = roll
        self.mark = []
        self.num = num
        for i in range(self.num):
            self.mark.append(0)

    def setScore(self,i,score):
        self.mark[i-1]=score
    
    def getScore(self,i):
        print(i,"th score is: ",self.mark[i-1])
    
    def getAvgScore(self):
        sum = reduce(lambda x,y : x+y , self.mark)
        sum /= len(self.mark)
        print("Average marks are: ",sum)
    
    def getMaxScore(self):
        max = reduce(lambda x,y : x if x>y else y, self.mark)
        print("Highest mark is: ",max)
    
def main():
    student1 = classroom("Arjun",20,4)
    student2 = classroom("Arju",22,4)
    student1.setScore(1,87)
    student1.setScore(2,78)
    student1.setScore(3,92)
    student1.setScore(4,66)
    student2.setScore(1,99)
    student2.setScore(2,97)
    student2.setScore(3,100)
    student2.setScore(4,89)
    student1.getScore(3)
    student1.getAvgScore()
    student2.getScore(2)
    student2.getAvgScore()
    student1.getMaxScore()
    student2.getMaxScore()

main()