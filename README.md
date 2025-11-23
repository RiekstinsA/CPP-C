# C/C++

### 1. strings.c
Dinamiska virkne C valodā.  
Realizēta kapacitātes palielināšana (realloc ×2), garuma uzskaite un append funkcija.

### 2. item_container.cpp
Konteiners ar "std::unique_ptr<T[]>" iekšpusē.  
Ir move konstruktors un move piešķiršanas operators, 
"operator[]" (const un parastais), "size()" metode.

### 3. car_park.cpp
Auto stāvvietas sistēma:  
- klase "Vehicle" → "Car"  
- dinamisks masīvs ar "Car**"  
- operatori "+=" un "<<"  
- pašizveidots izņēmums "OverflowException"  
- try-catch bloki un pareiza atmiņas atbrīvošana

### 4. memory.c
Fiksēta izmēra atmiņas pūls (memory pool).  
Piešķir bloku ar konstantu laiku (O(1)), bez fragmentācijas, 
viss pūls tiek atbrīvots vienā reizē.
