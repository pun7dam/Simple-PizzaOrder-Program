
(defclass pizza ()
   (
		(size :accessor pizza-size)
		(price :accessor pizza-price)	 
		(topingList :accessor pizza-topingList)	
		(countToping :accessor pizza-countToping)
	   (headerInfo :reader headerInfo)
	   (headerToppingInfo :reader headerToppingInfo)
	   (PizzaSetup :reader PizzaSetup)
	   (addTopping :reader addTopping)
   )
)

(defclass order ()
   (
		(name :accessor order-name)
		(phone :accessor order-phone)
		(address :accessor order-address)
		(orderArray :accessor order-orderArray)
		(type :accessor order-type)
		(addOrder :reader addOrder)
		(cartOrderInfo :reader cartOrderInfo)
		(clearCartOrder :reader clearCartOrder)
		(shipmentSummary :reader shipmentSummary)
		
		
   )
)

(setf ListTopping (make-array '(7)))
(setf (aref ListTopping 0) "Bacon")
(setf (aref ListTopping 1) "Olives")
(setf (aref ListTopping 2) "Ham")
(setf (aref ListTopping 3) "Mushrooms")
(setf (aref ListTopping 4) "Pineapple")
(setf (aref ListTopping 5) "Salami")
(setf (aref ListTopping 6) "Anchovies")

(setf MAXTOPPING 4) 
(setf DeliveryCharge 8)
(setf PriceEachTopping 1)
(setf orderCounter 0)

(setf orderObj (make-instance 'order))
(setf orderPizzaList (make-array '(100)))

;Displaying Pizza menu and operational information 
(defun headerInfo ((object pizza))
	(write-line "|----------------------------------------|")
	(write-line "| 0 for returning to order section       |")
	(write-line "|----------------------------------------|")
	(write-line "|-----------------------------------------------|");
	(write-line "| Pizza Shop ");
	(write-line "|-----------------------------------------------|");
	(write-line "|Press 0, 1, 2, 3, 4, 5 and 6 for the operations|");
	(write-line "|-----------------------------------------------|");
	(write-line "| 0: Exit");
	(write-line "| 1: For Small Pizza");
	(write-line "| 2: For Medium Pizza");
	(write-line "| 3: For Large  Pizza");
	(write-line "| 4: View Order Cart");
	(write-line "| 5: For Order Shipment");
	(write-line "| 6: Clear Order Cart");
	(write-line "|-----------------------------------------------|");
)

;Displaying list of topping available for the pizza
(defun headerToppingInfo ((object pizza))
	(write-line "|----------------------------------------|")
	(write-line "|        Topping available are           |")
	(write-line "|----------------------------------------|")	
	(setq counter 0)  
	(loop for x in '("Bacon" "Olives"
			   "Ham"
			   "Mushrooms"
			   "Pineapple" 
			   "Salami"
			   "Anchovies")
	  do  (setq counter (+ counter 1))  
	  (format t "| ~d. ~s ~%" counter x))
	
	(write-line "|----------------------------------------|")
	(write-line "| 0 for returning to order section       |")
	(write-line "|----------------------------------------|")
)



;Operations based on selected Id option
(defun PizzaSetup ((object pizza))
	
	(setq operationInput -1)
	(loop while (not (eql operationInput 0))
        do
		(format t "~%Order Size: ")
		;  Taking input operation from the console.
		(setq operationInput (read))		
		(cond
			((= operationInput 0) ; For closing the application
				(write-line "Thank you for visiting Pizza shop")
			) 
			((= operationInput 1)  ; For Small pizza
				(setf item (make-instance 'pizza))
				(setf (pizza-size item) "Small")
				(setf (pizza-price item) 5)
				(headerToppingInfo item)		
				(addTopping item)
				(addOrder item)
			)
		  ((= operationInput 2) ; For Medium pizza
				(setf item (make-instance 'pizza))
				(setf (pizza-size item) "Medium")
				(setf (pizza-price item) 8)
				(headerToppingInfo item)		
				(addTopping item)
				(addOrder item)
		  )
		  ((= operationInput 3) ; For Large pizza
				(setf item (make-instance 'pizza))
				(setf (pizza-size item) "Large")
				(setf (pizza-price item) 12)
				(headerToppingInfo item)		
				(addTopping item)
				(addOrder item)
		   )
		  ((= operationInput 4) ; Display information of Order Cart
				(setf (order-type orderObj) "CART")
				(cartOrderInfo orderObj)
		  )
		  ((= operationInput 5) ; Order summary display				
				(shipmentSummary orderObj)
				(setf (order-type orderObj) "SHIPMENT")
				(clearCartOrder orderObj)
		  )
		  ((= operationInput 6) ; Clearing cart information.
				(setf (order-type orderObj) "CLEAR")
				(clearCartOrder orderObj)
		  )		  
		  (t (format t "Invalid Order operation Id.~%"))
		)
	)	
)	


;Displaying all order array information for odered completion
(defun shipmentSummary ((object orderObj))
	(cond
		((>= orderCounter 1)
			(format t "|-----------------------------------------------|~%");
			(format t "|     Shipment Information ~%");
			(format t "| Note: Additional delivery $~d charge if total is less than $30 |~%" DeliveryCharge);
			(format t "|-----------------------------------------------|~%");
			(format t "|Press 0, 1, 2 and for the operations ~%");
			(format t "|-----------------------------------------------|~%");
			(format t "| 0: Return to Main Menu ~%");
			(format t "| 1: Self Collect ~%");
			(format t "| 2: Delivery ~%");
			(format t "|-----------------------------------------------|~%");
			(setq shipmentMethodId  "")			
			(format t "Shipment Method Type No.: ")
			(setq shipmentMethodId (read))
			(cond
				((= shipmentMethodId 0) ; For Returning to main menu
					(write-line "Returned to Main menu")
				)
				((= shipmentMethodId 1) ; Self collection from the shop
					(format t "Your name: ")
					(setf (order-name orderObj) (read))
					(format t "Your phone: ")	
					(setf (order-phone orderObj) (read))
					
					(format t "~% Your order summary ~%")
					(format t "Name: ~s    Phone: ~d ~%" (order-name orderObj) (order-phone orderObj))
					
					(setf (order-type orderObj) "SELF")
					(cartOrderInfo orderObj)					
					(format t "~%Thank you for ordering.~%~%Your new order, please.~%~%");
				)
				((= shipmentMethodId 2) ; For delivery
					(format t "Your name: ")
					(setf (order-name orderObj) (read))
					(format t "Your phone: ")	
					(setf (order-phone orderObj) (read))
					(format t "Your address: ")
					(setf (order-address orderObj) (read))
					(format t "~% Your order summary ~%")
					(format t "Name: ~s    Phone: ~d  Address: ~s ~%" (order-name orderObj) (order-phone orderObj) (order-address orderObj))
					
					(setf (order-type orderObj) "DELIVERY")
					(cartOrderInfo orderObj)					
					(format t "~%Thank you for ordering.~%~%Your new order, please.~%~%");
				)
				(t (format t "~%Invaid method Id. Check shipment method type Id.~%~%"));
			)
		)
		(t (format t "No pizza items in the order cart. Make your order.~%~%"))
	)		
)

; Adding pizza object into order array i.e. orderPizzaList	 
(defun addOrder ((object pizza))
	;(print (pizza-price object))
	;(print (pizza-size object))
	;(print (pizza-topingList object))
	(format t "~%Order has been added.~%~%")	
	(setf (aref orderPizzaList orderCounter) object)
	(setq orderCounter (+ orderCounter 1))
		
	;(setf (order-orderArray orderObj) object)		
	;(format t "~s ~%" (order-orderArray orderObj))
	;(print (order-orderArray orderObj))
	
)


; Clearing order array list and orderCounter
(defun clearCartOrder((object orderObj))		
	(cond
		((>= orderCounter 1)
			(cond
				((equal (order-type orderObj) "SHIPMENT")					
					(setf orderPizzaList (make-array '(100)))
					(setq orderCounter 0)					
				)
				((equal (order-type orderObj) "CLEAR")
					(setf orderPizzaList (make-array '(100)))
					(setq orderCounter 0)
					(format t "Removed Pizza items from the Order cart.~%")  
				)
			)
		)
		(t (format t "Order cart is already empty.~%~%"))
	)	
)


;Handles and display order array information
(defun cartOrderInfo((object orderObj))
	(setq total 0)
	(format t "|---------------------------------------------------|~%")
	(format t "|         PIZZA ITEMS    ~%")
	(format t "|---------------------------------------------------|~%");
	(setq count orderCounter)
	(setq count (- count 1))	
	(cond
		((>= count 0)
			(format t "| Size     Price     Toppings ~%");
			(format t "|---------------------------------------------------|~%");
			(loop while (>= count 0) 
			 do 
				(setf pizza (aref orderPizzaList count))				
				(setq total (+ total (pizza-price pizza)))
				;(format t "~s ~%" (pizza-size pizza))
				;(format t "~d ~%" (pizza-price pizza))
				;(format t "count: ~d ~%" count)
				(cond
					((<= (pizza-countToping pizza) 0)	
						(setq builder (format nil "| ~s  $~d  No topping.~%  " (pizza-size pizza) (pizza-price pizza)))																	
					)
					(t ; default case						
						(setq countTemp -1)													
						(setq total (+ total  (pizza-countToping pizza))); 
						; counter starts from zero.Som counter = 0 means one 1.
						(setq newBuilder (format nil "| ~s  $~d  ~s (each $~d)  ~%   " (pizza-size pizza) (pizza-price pizza) (pizza-topingList pizza) PriceEachTopping))						
						(write-line newBuilder)
					)
				)				
				;(write-line builder)
				
				;(format t "Topping: ~s ~%" (pizza-topingList pizza))
				;(print (pizza-countToping pizza))
				;(setq MyListLength (length (pizza-topingList pizza)))
				;(print MyListLength)
				
				(setq count (- count 1))
			)			
			(setq extraCharge 0)
			(cond
				((equal (order-type orderObj) "DELIVERY") 
					(cond
						((< total 30) 
							(setq total (+ total DeliveryCharge))
							(setq extraCharge DeliveryCharge)
						)
					)	
				)	
			)	
			(format t "|--------------------------------------------------|~%");
			(format t "|           Extra charge:$~d ~%" extraCharge);
			(format t "| Total     Order:~d     $~d ~%" orderCounter total);
		)
		(t (format t "|Empty pizza items in order cart.~%"))
	)		
	(format t "|---------------------------------------------------|~%");
			
)


(defun addTopping ((object item))
    (setq toppingNo -1)
	(setf countToping 0)
	(setf tempTopping "")
    (write-line "Select the topping types.")
    ; if not equal to zero, then loop continues
    (loop while (not (eql toppingNo 0)) 
        do  
        (write-line "Topping type No.: ")
        (setq toppingNo (read))
		;Outer Switch case i.e o, 1 --7 and above 7
		(cond
			((= toppingNo 0) (format t "returned to main menu.~%~%")) 
			; Inner switch case i.e. Max topping check and 
			((OR(= toppingNo 1) (= toppingNo 2) (= toppingNo 3) (= toppingNo 4) 
			  (= toppingNo 5) (= toppingNo 6) (= toppingNo 7)) 			  		  
			  (cond
					((>= countToping MAXTOPPING)
						(format t "~% Maximum topping reached i.e ~d~%" countToping)
						(format t "~% Type zero '0' for return: ")
						(setq toppingNo (read))
						(if (eql toppingNo 0) ; toppingNo equals to 0 then return to main menu
							(format t "~% returned to main menu.~%~% ")
							(format t "~% Invalid value.~%~% ")
						)
					) 
					((> toppingNo 7) 
						(format t "~% Topping order not found.Try again!~%~%")
					)				  
					(t ; default case						
						(setq temp (- toppingNo 1))	
						(setq tempTopping (cons (aref ListTopping temp) tempTopping))						
						(setq countToping (+ countToping 1))
						(format t "~s has been added. ~%" (aref ListTopping temp))	
						;(print tempTopping)
					)
				)				
			)
		    ; default case if not match any case above Outer switch case
		    (t (format t "Invalid topping type Id. Check Id.~%~%"))
		)
		(setf (pizza-countToping item) countToping)
		(setf (pizza-topingList item) tempTopping)
    ) 
)
		
		
            
           


;---------------------------------------
; Starting point of program
;object creation then function calling
(setf pz (make-instance 'pizza))
(headerInfo pz)
(PizzaSetup pz)
;---------------------------------------
