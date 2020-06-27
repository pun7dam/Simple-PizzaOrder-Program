from Pizza import Pizza

class Order:
    name= "";
    phone = 0;
    address = "";
    listOrder = [];
    def __init__(self):
        '''
        Constructor
        '''
    
    def clear(self):
        self.name="";     
        self.phone = 0;
        self.address = "";
        self.listOrder = [];
    
    
    