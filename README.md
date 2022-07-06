# Introduction:

In this project , we have assumed that maximum number of banks is given and that is used as MAX and the maximum number of currencies
available is N

We have taken currencies as numbers and any number represents a specific currency (NOTE:the inputs are taken as a string which gets converted into a number)

We have created a struct Graph which stores the name of bank,graph of bank,and whether the currency is there or not in the bank.

Struct Edge has the src as the currency to be converted and dest as the currency to which it has to be converted and weight as the
cost of conversion in terms of standard currency.

Struct Node has the currency (in form of number),weight(cost of conversion),name(optional),pointer to another node.

Struct stTable is used for best way path.It is used in Djistra.
We used Queue's in Djistra for best way path and heap's for low complexity.

//////////////////////////

# Compilation

Run generator.c to create the required text files.
	>gcc generator.c
	>./a.out>file.txt
Then run input.c to compute the files.
	>gcc input2.c
	>./a.out

//////////////////////////
# Instructions:

    1.ADDBANK
For the AddBank function we used CreateGraph function which has bank name,number of vertices     (currencies),takes which currencies is to be added,array of currencies available  in the bank.
If array of conversions available in the bank at beginning is given  they can be inserted by AddConversion function.

Example :    ADDBANK
            BOA 3 3   // 4 stands for no.of to been added // 6 stands for no.of pre ADDCONVERSION
             3 4 1      // 3 and 4 stands for currency numbers
             3 4 10     // here first column represent source(from)
             1 4 3      // here second column represents destination
             3 1 8      // here third column represents  weight of edge

    2.DeleteBank
       In these we delete the entire data of the bank including the conversions.If not it shows error

Eaxmple :    DeleteBank
             3

    3.AddCurrencyInBank
       In this we take bank name and curr name.If not it shows error
Example :   AddCurrencyInBank
             3 2      // 3 is bank name 2 is currency need to add
    
    4.DeleteCurrencyInBank
      In this we take bank name and curr name.If not exist it shows error
Example : DeleteCurrencyInBank
           3 2       // 3 is bank and 2 is currency need to delete

    5.AddConversion
     In this we add the Exchange between two currency in a bank. If not exist shows error.
Example :  AddConversion
            3 4 5 12  // 3 is bank name,4 is from which currency,5 to which currency,12 is     
                          excange rate 

    6.DeleteConversion
       In this we delete Exchange between two currency in abank.If not exist shows error.
Example :  DeleteConversion
            3 4 5 12  //3 is bank name,4 is from which currency,5 to which currency,12 is     
                          excange rate 

    7.BestWay
      In this we say about best exchange between two currency in which bank.If not exist shows errors.
Example :  BestWay
            1 3     // 1 and 3 are currency,finds the best way
        shows as this
        Bank :BOA cost: 12   // cost is Exhange cost from 1 to 3
        Path : 3<-4<-1   

    8.printbankinfo
      In this we take the bank name and shows the all convesions.If not exist shows errors
Example :  printbankinfo
            2
        Citi     // citi is bank name
        1 —> 3 (9)	1 —> 2 (1)	// 1->3 indiactes the Exchange from currency 1 to 3 with cost 9 
        2 —> 5 (6)	2 —> 4 (2)	
        3 —> 4 (8)	3 —> 1 (4)  

    9.Exit
     In this it exit from program.

////////////////////////////////////////
# Time complexicty : O(V)

For createGraph function which uses malloc and some stringcopy functions and loops

Time complexicty : O(N*V) worst-case
For printpath function which prints every conversion in the bank,So it goes every end of the linked(so for every convesion takes O(V)) and name of the bank.

Time complexity: O(N)
For DeleteBank function we used the function deletebank function which takes the address of bank as the input.

Time complexity:O(1)
For AddCurrency we just convert the corresponding currency number in the array of currencies in bank to AVAILABLE.If the bank is not added yet it prints NOT possible.

Time complexity: O(1)
For Deletecurrency we used DeleteList function which takes bank address and currency number as input. It deletes the entire  linked list(neighbours) corresponding to that currency number and the nodes(It nodes take time complexicty O(V)) in which destination is that currency.
If bank is not added it prints NOTPOSSIBLE.

Time complexity: O(c)  where c is constant
For AddConversion we take the address of bank and currencies involved in the conversion and the cost of conversion as the input.If the currency is not availble or if the bank is not added then it prints NOTPOSSIBLE.

Time complexity: O((num+V)*(ElogV+VlogE))  where e is edge and v is vertices
For bestpath we used Djistra algorithm which runs over all the banks added and find out the least cost.

# Limitations

Our program currently accepts the universal set of currency names in the beginning of the program. We have created a generator that generates random 3 letter strings to represent these names.
We also set the max number of currencies and max number of banks before the program begins. This shouldn't pose a problem considering there are only 180 currencies in the world and our program can handle much more than that.

It also uses numbers to represent banknames when calling function although it does print out the actual name of the bank when the 'print bank info' or the 'best path' option is chosen.




