%ifndef NULL                    ;Установим NULL
    %define NULL 0
%endif

%ifndef LAST_ELEMENT            ;Установим последний элемент
    %define LAST_ELEMENT NULL
%endif

%macro colon 2
   %2: dq   %2_key, %2_value, LAST_ELEMENT
   %2_key: db %1, 0
   %2_value:
   %define LAST_ELEMENT %2 
%endmacro
