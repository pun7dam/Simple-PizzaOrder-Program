from Pizza import Pizza
from Order import Order
from Topping import Topping


class Shop:  
    order = Order(); 
    top = Topping();
    priceEachTopping = 1;
    deliveryCharge = 8;
    
    def __init__(self):
        self.headerInfo();
        self.pizzaSetup();
    
    # List of menu option available for the shop.
    def headerInfo(self):
        print("|-----------------------------------------------|");
        print("|\t Pizza Shop \t\t\t\t|");
        print("|-----------------------------------------------|");
        print("|Press 0, 1, 2, 3, 4, 5 and 6 for the operations|");
        print("|-----------------------------------------------|");
        print("| 0: Exit \t\t\t\t\t|");
        print("| 1: For Small Pizza  \t\t\t\t|");
        print("| 2: For Medium Pizza \t\t\t\t|");
        print("| 3: For Large  Pizza \t\t\t\t|");
        print("| 4: View Order Cart \t\t\t|\t\t");
        print("| 5: For Order Shipment \t\t\t|");
        print("| 6: Clear Order Cart \t\t\t|\t\t");
        print("|-----------------------------------------------|\n");
        
    
    # Starting of the operation of pizza.
    def pizzaSetup(self):    
        self.operationInput="";
        while True:              
            print("Order Size: ")
            #Taking input operation from the console. 
            self.operationInput = input()  
            if self.operationInput == "0":
                print("Thank you for visiting Pizza shop\n");
                quit();                    
                break
            elif self.operationInput == "1": 
                sPizza = Pizza();
                self.top.initLoad();
                sPizza.listToping = self.top.getToping();
                self.top.clear();
                sPizza.price = 5.0;
                sPizza.size = "SMALL";                
                self.order.listOrder.append(sPizza);
                self.headerInfo();
                  
            elif self.operationInput == "2":
                mPizza = Pizza();
                self.top.initLoad();
                mPizza.listToping = self.top.getToping();
                self.top.clear();
                mPizza.price = 8.0;
                mPizza.size = "MEDIUM";                
                self.order.listOrder.append(mPizza); 
                self.headerInfo();
                
            elif self.operationInput == "3":
                lPizza = Pizza();
                self.top.initLoad();
                lPizza.listToping = self.top.getToping();
                self.top.clear();
                lPizza.price = 12.0;
                lPizza.size = "LARGE";                
                self.order.listOrder.append(lPizza); 
                self.headerInfo();                
                    
            elif self.operationInput == "4": 
                self.orderCart("CARDORDER");
            
            elif self.operationInput == "5": 
                self.shipmentSummary();
                
            elif self.operationInput == "6": 
                self.clearOrderCart();
            else:                
                print("Invalid Order operation Id");
              
            if self.operationInput == "0":  
                break        
                              
    
    # Displaying list of information on the orders
    def orderCart(self, method):
        total = 0.0;
        print("|---------------------------------------------------------------|");
        print("|\t\t PIZZA ITEMS \t\t\t\t\t|");
        if len(self.order.listOrder) > 0:
            print("| Size \t\t Price \t\t\t Toppings \t\t|");
            print("|---------------------------------------------------------------|");
            # p is Pizza type and listOrder is array of pizza
            for p in self.order.listOrder:                 
                builder = "| " + str(p.size) + "\t\t $" + str(p.price) + "\t\t";
                total = total + p.price;
                if len(p.listToping)== 0:
                    builder = builder + "No topping. \t\t|\n";
                    print(builder);
                    print("|---------------------------------------------------------------|");
                else:
                    countTemp = 0;
                    total =total + len(p.listToping) * self.priceEachTopping;
                    for t in p.listToping:
                        if countTemp == 0:
                            print(builder , t , "  each $" , self.priceEachTopping , "\t|");
                            countTemp= countTemp+1;
                        else:
                            print("|\t\t\t\t\t" , t , "  each $" , self.priceEachTopping , "\t|");
                        
                    
            print("|---------------------------------------------------------------|");
            
            if method == "DELIVERY":
                if total < 30: # charge is $8 for delivery option if tota is < 30
                    total = total + self.deliveryCharge;               
            
            print("| \t\tExtra charge $:" ,self.deliveryCharge);
            print("| Total \t Order:" , len(self.order.listOrder) , "\t\t $" , total , "\t\t\t|");
        else:
            print("| Empty pizza items in order cart.\t\t|");
        
        print("|---------------------------------------------------------------|");
    

    # Shipment information display.
    def shipmentSummary(self):    
        if not self.CheckOrderCart():        
            print("No pizza items in the order cart. Make your order");
        else:
            print("|-----------------------------------------------|");
            print("|\t Shipment Information \t\t|");
            print("| Note: Additional " , self.deliveryCharge , " charge if total is less than $30 \t\t|");
            print("|-----------------------------------------------|");
            print("|Press 0, 1, 2 and for the operations|");
            print("|-----------------------------------------------|");
            print("| 0: Return to Main Menu \t\t\t\t\t|\n");
            print("| 1: Self Collect \t\t\t\t|\n");
            print("| 2: Delivery \t\t\t\t|\n");
            print("|-----------------------------------------------|\n");
            shipmentMethodId= "";
            while True:            
                name = ""
                address = "";
                phone = 0;
                print("Shipment Method Type No.: ");                
                shipmentMethodId = input();
                if(shipmentMethodId == "0"):
                    break;
                elif(shipmentMethodId == "1"):   # for self pickup option              
                    name = self.CheckString("Name");
                    phone = self.CheckNumber("Phone");
                    self.order.name = name;
                    self.order.phone =phone;

                    print("\n Your order summary");
                    print("Name: " , self.order.name , " \t Phone: " , self.order.phone , "\n");
                    print("Shipment Type: COLLECT");
                    
                    self.orderCart("COLLECT");
                    self.clearOrderCart("SHIPMENT");
                    
                    shipmentMethodId = "0"; 
                    print("\nYour new order.Please");
                    break;
                elif(shipmentMethodId == "2"):   # For delivery option   
                    name = self.CheckString("Name");
                    phone = self.CheckNumber("Phone");
                    address = self.CheckString("Address");
                    self.order.name = name;
                    self.order.phone =phone;
                    self.order.adddress =address;
                    print("\nYour order summary");
                    print("Name: " , self.order.name , " \t Phone: " , self.order.phone , "\t Address: " , self.order.adddress);
                    print("Shipment Type: DELIVERY");
                    self.orderCart("DELIVERY");
                    self.clearOrderCart("SHIPMENT");
                    
                    shipmentMethodId = "0";
                    print("\nYour new order.Please");
                    break;
                else:
                    print("Invaid method Id. Check shipment method type Id.\n");
     
    
    # Clearing information of orders
    def clearOrderCart(self, shipment=""):
        if (shipment == "SHIPMENT"):
            self.order.clear();             
        elif len(self.order.listOrder) > 0:
            self.order.clear();
            print("Removed Pizza items in the Order cart.\n")        
        else:       
            print("Order cart is already empy.")
        
                  
                    
    def CheckOrderCart(self):    
        if len(self.order.listOrder) > 0:        
            return True
        else:       
            return None
        
    def CheckString(self, n):    
        temp = "";        
        while True:              
            print("\n Your " , n , ": ");
            temp = input();             
            if(len(temp) > 0):
                break;
        return temp;     
            

    def CheckNumber(self, p):
        temp = 0;
        while True: 
            try:             
                print("\n Your " , p , ": ");
                temp = input();                
                if(temp.isdigit()): 
                    break;
            except:
                print("Invaid phone number.")
                
        return temp;        
    
    
    

