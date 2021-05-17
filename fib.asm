;提示输入字符串
inNum segment
    db 'please input a number: ','$' ;length=23 
inNum ends             
;警告
warn segment
    w_range db 'the number is out of range...','$' ;length=29
    w_below_zero db 'the number must be positive!','$' ;length=28 
    w_restart db 'press any key to continue...','$';length=28    
    is_warn dw 0
warn ends
;设置输入数字字符栈
num_input segment
    db 32 dup(0)  
    top dw 0;数字栈顶 
    fib_length dw 0;序列长度
num_input ends     
;设置栈段
stk segment
    db 200h dup(0)   
stk ends
;显示字符串  

;设置16进制的数据段
radix_16_stk segment
    tmp_16 dd 0
    f1_16 dd 0
    f2_16 dd 0
radix_16_stk ends
;设置10进制的数据段   
radix_10_stk segment
    tmp_10 db 5 dup(0)
    f1_10 db 5 dup(0)
    f2_10 db 5 dup(0)
radix_10_stk ends

code segment 
    
main proc
start:      
;初始化各段
    mov ax,stk
    mov ss,ax
    mov sp,0    
    call clean_screen
    
to_get_num:   
    mov ax,num_input
    mov ds,ax
    mov bx,0   
    mov word ptr ds:[32],bx;栈顶置0 
    call cancel_warn
    call show_inNum  
    call get_num 
    call do_16   
    mov dx,1
    jmp short restart
    
modern:
    cmp dx,1
    je to_print_16
    call print_10       
    jmp short restart
    
to_print_16:  
    call print_16     
              
    ;要不要重开，小老弟？  
restart:
    mov ah,07h
    int 21h    
    call clean_screen
    cmp al,'q' ;exit
    je to_end
    cmp al,'Q' ;exit  
    je to_end
    cmp al,' '  ;切换16进制或者10进制表达
    jne short to_get_num   
    
    mov bx,warn
    mov ds,bx
    mov bx,offset is_warn
    cmp word ptr [bx],1
    je  short to_get_num
    
    
    cmp dx,1
    je ok1
    mov dx,1
    jmp short modern  
ok1:
    mov dx,0  
    jmp short modern
    
to_end:
    call end_pro  
main endp     

clean_screen proc      
;     push ax  
;     mov ax,3
;     int 10h
;     pop ax         
    push ax
    mov  ah,0fh
    int  10h
    mov  ah,0
    int  10h  
    pop ax
;下面这段在emu8086特别慢，不推荐使用
;    push bx
;    push es
;    push cx
;    push ax
;    
;    mov bx,0b800h
;    mov es,bx
;    mov bx,0
;    mov cx,4000
;clean:
;    mov ax,0
;    mov es:[bx],ax
;    add bx,2
;    loop clean   
;    
;    pop ax
;    pop cx
;    pop es
;    pop bx
    ret       
clean_screen endp
                 
show_inNum proc
    push ax
    push ds
    push dx
    push bx  
    push cx
    push di
             
    ;转移光标位置
    mov ah,02h
    mov bh,0
    mov dh,12
    mov dl,10
    int 10h
             
    ;显示字符串
    mov ax,inNum
    mov ds,ax
    mov dx,0h
    mov ah,09h 
    int 21h       
    
    mov ax,0b800h
    mov ds,ax
    mov di,160*12+21
    mov cx,22
show_s:
    mov ds:[di],11110010b
    inc di
    inc di
    loop show_s
    
    pop di
    pop cx
    pop dx
    pop ds
    pop ax 
    pop bx
    ret  
show_inNum endp
    
get_num proc 
    push ax
    push ds
    push dx        
    
    mov ax,num_input
    mov ds,ax
    mov si,0    
    call get_num_
         
    pop dx
    pop ds
    pop ax 
    ret 
get_num endp

get_num_ proc
    push ax  
_get_num_:
    mov ah,0
    int 16h;INT16H 00H读取键盘字符
    cmp al,30h  ;数字？
    jb no_digit
     
    mov ah,0
    call num_stk  
    
    mov ah,2
    call num_stk
    
    jmp _get_num_   
    pop ax     
get_num_ endp    

;以ah为选项，ah=0、1、2分别代表入栈、出栈、显示字符串             
num_stk proc 
    jmp short num_start
num_start:
    push bx
    push dx
    push di
    
    cmp ah,0
    je num_push  
    
    cmp ah,1
    je num_pop     
    
    cmp ah,2
    je num_show
    
    jmp sret
        
num_push:
    mov bx,top      
    mov [bx],al 
    mov [bx+1],'$'
    inc top
    jmp sret
   
num_pop:
    cmp top,0
    je sret 
    dec top
    mov bx,top
    mov al,[bx];将出栈字符放入al中 
    mov [bx],'$' 
    jmp sret
       
num_show:     
    call clean_screen
    call show_inNum   
    cmp top,0 
    je sret                  
    
    ;移动光标位置
    mov ah,02h
    mov bh,0
    mov dh,12
    mov dl,10+23
    int 10h          
    
    ;显示字符串       
    mov ax,num_input
    mov ds,ax
    mov dx,0h
    mov ah,09h
    int 21h 
    
sret:
    pop di
    pop dx
    pop bx
    ret
num_stk endp
                
no_digit proc  
    cmp ah,0ch
    je minus  
    
    cmp ah,0eh
    je backspace 
    
    cmp ah,1ch
    je enter  
    
    jmp _get_num_
   
minus:
    mov ah,0
    call num_stk
    
    mov ah,2
    call num_stk
    
    jmp _get_num_
backspace:
    mov ah,1
    call num_stk
    
    mov ah,2
    call num_stk
    
    jmp _get_num_
    
enter:
    mov ah,0   
    mov al,'$'
    call num_stk
    
    pop ax
    ret
no_digit endp          
   
end_pro proc
    mov ax,4c00h
    int 21h  
end_pro endp
   
do_16 proc    
    call clean_screen
    cmp top,0 
    je do_16_ret    
    push ax
    push ds
    push si
    push bx
    push cx 
    push dx
    
    mov ax,num_input
    mov ds,ax      
    mov ax,0
    mov si,0      
    mov bx,0   
    mov dx,0
    mov cx,top
    dec cx  
    ;获取十进制数并放在ax中      
    cmp byte ptr ds:[si],'-'
    je below_zero_10             
    cmp byte ptr ds:[si],'$'    
    je do_16_ret
get_num_10:      
    mov bl,byte ptr ds:[si] 
    sub bl,30h
    add al,bl
    adc ah,0
    mov bx,10       
    mul bx
    inc si
    loop get_num_10  
    mov bx,10 
    div bx
    ;ax的值应小于等于49
    cmp ax,31h 
    ja out_range_10 
    cmp dx,0
    ja out_range_10 
    cmp ax,0
    je do_16_ret  
    
    mov cx,ax         
    push si
    mov si,offset fib_length 
    mov [si],cx 
    pop si
    call print_16
    jmp short do_16_ret  
    
out_range_10:  
    call set_warn
    call out_range 
    jmp short do_16_ret   
              
below_zero_10: 
    call set_warn
    call below_zero 
    jmp short do_16_ret
    
do_16_ret: 
    pop dx
    pop cx
    pop bx
    pop si
    pop ds
    pop ax
    ret                                                
do_16 endp
       
out_range proc
    call clean_screen
    push ax
    push bx
    push dx
    push ds   
    push di
    push cx
    ;移动光标位置
    mov ah,02h
    mov bh,0
    mov dh,12
    mov dl,25
    int 10h          
    
    ;显示字符串       
    mov ax,warn
    mov ds,ax
    mov dx,offset w_range
    mov ah,09h
    int 21h     
    
    mov ax,0b800h
    mov ds,ax
    mov di,160*12+51
    mov cx,29
show_out0:
    mov ds:[di],11110100b
    inc di
    inc di
    loop show_out0
    ;显示press to continue
    mov ah,02h
    mov bh,0
    mov dh,13
    mov dl,25
    int 10h

    mov ax,warn
    mov ds,ax
    mov dx,offset w_restart
    mov ah,09h
    int 21h
    
    mov ax,0b800h
    mov ds,ax
    mov di,160*13+51
    mov cx,28
show_out1:
    mov ds:[di],11110100b
    inc di
    inc di
    loop show_out1
        
    pop cx
    pop di
    pop ds
    pop dx
    pop bx
    pop ax
    ret
out_range endp
                     
below_zero proc
    call clean_screen
    push ax
    push bx
    push dx
    push ds   
    push di
    push cx
    ;移动光标位置
    mov ah,02h
    mov bh,0
    mov dh,12
    mov dl,25
    int 10h          
    
    ;显示字符串       
    mov ax,warn
    mov ds,ax
    mov dx,offset w_below_zero
    mov ah,09h
    int 21h     
    
    mov ax,0b800h
    mov ds,ax
    mov di,160*12+51
    mov cx,28
show_out2:
    mov ds:[di],11110100b
    inc di
    inc di
    loop show_out2
    ;显示press to continue
    mov ah,02h
    mov bh,0
    mov dh,13
    mov dl,25
    int 10h

    mov ax,warn
    mov ds,ax
    mov dx,offset w_restart
    mov ah,09h
    int 21h
    
    mov ax,0b800h
    mov ds,ax
    mov di,160*13+51
    mov cx,28
show_out3:
    mov ds:[di],11110100b
    inc di
    inc di
    loop show_out3
        
    pop cx
    pop di
    pop ds
    pop dx
    pop bx
    pop ax
    ret
below_zero endp

set_warn proc  ;set warning
    push ax
    push ds
    push di           
    
    mov ax,warn
    mov ds,ax
    mov di,offset is_warn  
    mov word ptr [di],1  
    
    pop di
    pop ds
    pop ax    
    ret
set_warn endp   

cancel_warn proc  ;cancel warning
    push ax
    push ds  
    push di     
    
    mov ax,warn
    mov ds,ax
    mov di,offset is_warn  
    mov word ptr [di],0  
    
    pop di
    pop ds
    pop ax    
    ret
cancel_warn endp   

;radix_16_stk segment
;    tmp_16 dd 0
;    f1_16 dd 0
;    f2_16 dd 0
;radix_16_stk ends   
   
reset_16 proc   
    push bx
    push cx
    push ds
    push di
    
    mov bx,radix_16_stk  
    mov ds,bx
    mov di,offset tmp_16
    mov byte ptr [di],0  
    mov cx,3
    inc di 
reset_16_loop1:
    mov byte ptr [di],0  
    inc di
    loop reset_16_loop1
    
    mov di,offset f1_16
    mov byte ptr [di],0 
    mov cx,3
    inc di 
reset_16_loop2:
    mov byte ptr [di],0 
    inc di
    loop reset_16_loop2
    
    mov di,offset f2_16
    mov byte ptr [di],1  
    mov cx,3
    inc di 
reset_16_loop3:
    mov byte ptr [di],0 
    inc di
    loop reset_16_loop3
    
    pop di
    pop ds
    pop cx
    pop bx
    ret
reset_16 endp
    
print_16 proc 
    push di
    push si          
    push cx 
    push es  
    push bx
    push ax       
    
    call clean_screen  
    
    mov ax,num_input
    mov ds,ax
    mov si,offset fib_length
    mov cx,[si]
     
    call reset_16   
    
    mov bx,radix_16_stk  
    mov ds,bx  
    mov bx,0b800h 
    mov es,bx
    mov si,8
    mov bx,0    
final_loop_16:  
    push cx
    ;输出f2_16，并使得tmp=f2 f2=f1+f2 f1=tmp   
    mov ax,offset f2_16
    add ax,3
    mov di,ax
    mov cx,4  

show_f2_16:        
    mov al,byte ptr ds:[di]   
    push bx 
    mov bx,ax
    shr al,4
    mov ah,al;存高4位
    mov al,bl
    and al,00001111b;存低4位  
    pop bx      
           
    cmp ah,9
    jbe change_to_char_16_h    
    add ah,41h
    sub ah,10
    sub ah,30h
change_to_char_16_h:
    add ah,30h
    mov byte ptr es:[si],ah 
    mov ah,00000010b 
    mov byte ptr es:[si+1],ah
    add si,2
        
    cmp al,9
    jbe change_to_char_16_l 
    add al,41h
    sub al,10 
    sub al,30h  
change_to_char_16_l:
    add al,30h  
    mov byte ptr es:[si],al  
    mov al,00000010b 
    mov byte ptr es:[si+1],al
    add si,2
    dec di
    loop show_f2_16  
    add si,2 ;往后两个字节，为了保证数据间有间隔
    push si
      
    mov di,offset f2_16
    mov si,offset tmp_16   
    mov cx,2
swap_tmp_16:
    mov ax,word ptr [di]
    mov word ptr [si],ax
    add di,2
    add si,2
    loop swap_tmp_16   
    
    mov di,offset f1_16
    mov si,offset f2_16  
    mov cx,2    
    clc;清除进位
add_f2_16:
    mov ax,word ptr [di] 
    adc ax,word ptr [si] 
    pushf
    mov word ptr [si],ax   
    add di,2
    add si,2    
    popf
    loop add_f2_16 
    
    mov di,offset tmp_16
    mov si,offset f1_16
    mov cx,2
swap_f1_16:
    mov ax,word ptr [di]
    mov word ptr [si],ax
    add di,2
    add si,2
    loop swap_f1_16 
    
    pop si
    pop cx     
    inc bx
    cmp bx,8    
    jne ok2   
    add si,16  
    mov bx,0
ok2:
    loop final_loop_16       

    pop ax
    pop bx
    pop es
    pop cx
    pop si
    pop di
    ret
print_16 endp

;radix_10_stk segment
;    tmp_10 db 5 dup(0)
;    f1_10 db 5 dup(0)
;    f2_10 db 5 dup(0)
;radix_10_stk ends     

reset_10 proc 
    push bx  
    push cx
    push ds
    push di
    
    mov bx,radix_10_stk  
    mov ds,bx        
    
    mov di,offset tmp_10
    mov byte ptr [di],0  
    mov cx,4
    inc di 
reset_10_loop1:
    mov byte ptr [di],0 
    inc di
    loop reset_10_loop1
    
    mov di,offset f1_10
    mov byte ptr [di],0 
    mov cx,4
    inc di 
reset_10_loop2:
    mov byte ptr [di],0    
    inc di
    loop reset_10_loop2
    
    mov di,offset f2_10
    mov byte ptr [di],1  
    mov cx,4
    inc di 
reset_10_loop3:
    mov byte ptr [di],0 
    inc di
    loop reset_10_loop3
    
    pop di
    pop ds
    pop cx
    pop bx
    ret
reset_10 endp

print_10 proc   
    push di
    push si          
    push cx 
    push es  
    push bx
    push ax  
    
    call clean_screen
    
    mov ax,num_input
    mov ds,ax
    mov si,offset fib_length
    mov cx,[si]
    
    call reset_10
    
    mov bx,radix_10_stk
    mov ds,bx
    mov bx,0b800h 
    mov es,bx
    mov si,2
    mov bx,0  
final_loop_10: 
    push bx
    push cx   
    
    mov ax,offset f2_10
    add ax,4     
    mov di,ax  
    mov cx,5  
show_f_10:  
    mov al,byte ptr ds:[di]   
    push bx 
    mov bx,ax
    shr al,4
    mov ah,al;存高4位
    mov al,bl
    and al,00001111b;存低4位  
    pop bx 
    
    add ah,30h 
    mov byte ptr es:[si],ah
    mov ah,00000010b   
    mov byte ptr es:[si+1],ah
    add si,2       
    
    add al,30h 
    mov byte ptr es:[si],al
    mov al,00000010b
    mov byte ptr es:[si+1],al
    add si,2 
    dec di
    loop show_f_10
    add si,2
    push si
    
    mov di,offset f2_10
    mov si,offset tmp_10  
    mov cx,5
swap_tmp_10:
    mov al,byte ptr [di]
    mov byte ptr [si],al 
    inc di
    inc si
    loop swap_tmp_10
    
    mov di,offset f1_10
    mov si,offset f2_10  
    mov cx,5
    clc    
add_f2_10:
    mov al,byte ptr [di]  
    adc al,byte ptr [si]  
    daa    
    pushf
    mov byte ptr [si],al
    inc di
    inc si   
    popf
    loop add_f2_10
      
    mov di,offset tmp_10
    mov si,offset f1_10  
    mov cx,5
swap_f1_10:
    mov al,byte ptr [di]
    mov byte ptr [si],al
    inc di
    inc si          
    loop swap_f1_10   
    
    pop si
    pop cx 
    pop bx 
    inc bx
    cmp bx,7    
    jne ok3   
    add si,6  
    mov bx,0
ok3:
    loop final_loop_10 
    
    pop ax
    pop bx
    pop es
    pop cx
    pop si
    pop di
    ret  
print_10 endp
                
code ends
end start
