
class Topping:
     
    ListTopping = ("Bacon", 
               "Olives", 
               "Ham", 
               "Mushrooms", 
               "Pineapple", 
               "Salami", 
               "Anchovies");
    
    MAXTOPPING = 4; 
    tempToping= [];
    
    def __init__(self):
        '''
        Constructor
        '''
                 
    def initLoad(self):
        self.headerInfo();
        self.addTopping(); 
    
    def getToping(self):
        return self.tempToping;
    
    def clear(self):
        self.tempToping=[];
        
    # Display of topping available for the pizza.
    def headerInfo(self):
        print("|----------------------------------------|");
        print("|\t Topping available are \t\t |");
        print("|----------------------------------------|");
        self.id = 1;
        for s in self.ListTopping:
            print("| ", self.id , ": " , s , "\t\t\t\t|");
            self.id = self.id + 1;
        
        print("|----------------------------------------|")
        print("| 0 for returning to order section \t\t|")
        print("|----------------------------------------|")
    
    # Adding list of topping to pizza
    def addTopping(self):  
        self.toppingNo = "-1"  
        self.countOrderTopping = 0
        print("Select the topping types.")
        while True:              
            print("Topping type No.: ")
            # Taking input operation from the console. 
            self.toppingNo = input()            
            if self.toppingNo == "0":
                break
            elif self.toppingNo > "0" and self.toppingNo <="7":   # Max 7 topping option available             
                if self.countOrderTopping > self.MAXTOPPING:                    
                    print("\n Maximum topping reached i.e " , self.countOrderTopping)
                    print("\n Type zero '0' for return: ")
                    self.toppingNo = input()
                    if self.toppingNo == "0":
                        break;                        
                    break;                    
                elif self.toppingNo > str(len(self.ListTopping)):
                    print("Topping order not found.Try again!.\n")
                else:          
                    # Adding choosen topping option to pizza.
                    self.tempToping.append(self.ListTopping[int(self.toppingNo) - 1]);
                    print(self.ListTopping[int(self.toppingNo) - 1] , " has been added.");
                    self.countOrderTopping= self.countOrderTopping+1
            else:                
                print("Invalid topping type Id. Check Id.\n");
              
            if self.toppingNo == "0":  # return to main menu option
                break 
                        
    
    
    
    
    
    
    