;提示输入字符串
inNum segment  
    in_n_count db 0     
    entered db 0
    in_n db 'please input a number(N): ','$' ;length=26 
    in_i db 'please input a number(I): ','$' ;length=26   
    in_m db 'please input a number(M): ','$' ;length=26 
inNum ends             
;警告
warn segment
    w_range db 'the number is out of range...','$' ;length=29
    w_below_zero db 'the number must be positive!','$' ;length=28 
    w_restart db 'press any key to continue...','$';length=28 
    w_end db 'are you kidding me? see you~','$';length=28   
    is_warn dw 0   
    w_count dw 0
warn ends
;设置输入数字字符栈
num_input segment
    db 32 dup(0)  
    top dw 0;数字栈顶 
    fib_length dw 0;序列长度  
num_input ends     
;保存上一次的初始数据
pre_data segment
    p_tmp_16 dw 5 dup(0)
    p_f1_16 dw 5 dup(0)
    p_f2_16 dw 5 dup(0)      
    p_tmp_10 dw 5 dup(0)
    p_f1_10 dw 5 dup(0)
    p_f2_10 dw 5 dup(0)
pre_data ends
;设置栈段
stk segment
    db 100h dup(0)   
stk ends
;显示字符串  

;设置16进制的数据段
radix_16_stk segment
    tmp_16 dw 5 dup(0)
    f1_16 dw 5 dup(0)
    f2_16 dw 5 dup(0)
radix_16_stk ends

code segment 
    
main proc
start:      
;初始化各段
    mov ax,stk
    mov ss,ax
    mov sp,0    
    call clean_screen
    
to_get_num:   
    mov ax,inNum
    mov ds,ax
    mov in_n_count,0
    mov entered,0
    mov ax,num_input
    mov ds,ax     
    mov top,0;栈顶置0  
    call reset_16
               
    call clean_screen
    call cancel_warn
    call show_inNum  
    call get_num  
    push ax       
    push bx
    push ds   
    
    call solve_num    
    mov bx,radix_16_stk 
    mov ds,bx
    mov f1_16,ax
    mov bx,pre_data
    mov ds,bx
    mov p_f1_16,ax 
         
    pop ds
    pop bx
    pop ax             
    
    call clean_screen
    mov top,0;栈顶置0  
    call cancel_warn  
    call show_inNum 
    call get_num 
    push ax       
    push bx
    push ds    
    
    call solve_num    
    mov bx,radix_16_stk 
    mov ds,bx
    mov f2_16,ax   
    mov bx,pre_data
    mov ds,bx
    mov p_f2_16,ax
      
    pop ds
    pop bx
    pop ax        
    
    call clean_screen
    mov top,0;栈顶置0 
    call cancel_warn   
    call show_inNum 
    call get_num  
    push ax
    call solve_num
    mov fib_length,ax
    pop ax
    
    call print_16  
    mov dx,1
    jmp short restart
    
pattern:
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
    jmp short pattern  
ok1:
    mov dx,0  
    jmp short pattern
    
to_end:
    call end_pro  
main endp     

clean_screen proc             
    push ax
    mov  ah,0fh
    int  10h
    mov  ah,0
    int  10h  
    pop ax
    ret       
clean_screen endp
                 
show_inNum proc
    push ax
    push ds
    push dx
    push bx  
    push cx
    push di
             
    ;显示字符串
    mov ax,inNum
    mov ds,ax  
    mov di,160*9+21  
        
    cmp in_n_count,0
    jne in_n_ok1
    ;转移光标位置
    mov ah,02h
    mov bh,0
    mov dh,10
    add dh,in_n_count
    mov dl,10
    int 10h 
    mov dx,offset in_n
    add di,160  
    mov ah,09h      
    int 21h  
    call show_num_style
in_n_ok1:   
    cmp in_n_count,1
    jne in_n_ok2
    ;转移光标位置
    mov ah,02h
    mov bh,0
    mov dh,10
    add dh,in_n_count
    mov dl,10
    int 10h  
    mov dx,offset in_i
    add di,160*2   
    mov ah,09h  
    int 21h  
    call show_num_style
in_n_ok2:  
    cmp in_n_count,2
    jb in_n_ok3 
    ;转移光标位置
    mov ah,02h
    mov bh,0
    mov dh,10
    add dh,in_n_count
    mov dl,10
    int 10h 
    mov dx,offset in_m
    add di,160*3  
    mov ah,09h
    int 21h  
    call show_num_style        
    
in_n_ok3:    
    pop di
    pop cx
    pop bx
    pop dx
    pop ds 
    pop ax
    ret  
show_inNum endp

show_num_style proc   
    push ax
    push ds
    push cx
    push di
    
    mov ax,0b800h
    mov ds,ax
    mov cx,25
show_s:
    mov byte ptr ds:[di],01110010b
    inc di
    inc di
    loop show_s       
    
    pop di
    pop cx
    pop ds
    pop ax
    ret   
show_num_style endp
   
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
    ;下面两步控制是否支持输入除数字外的可打印字符读入num_input     
    cmp al,39h
    ja no_digit
     
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
       
    mov ax,inNum
    mov ds,ax     
    mov dh,10  
    add dh,in_n_count   
    cmp entered,1
    jne n_s_ok1   
    mov entered,0
    inc in_n_count
;    cmp in_n_count,3
;    jne n_s_ok1
;    mov in_n_count,0             
n_s_ok1:  
    cmp top,0 
    je sret                  
    
    ;移动光标位置  
    mov ah,02h
    mov dl,10+26
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
    push ds
    mov ax,inNum
    mov ds,ax
    mov entered,1
    pop ds      
    
    mov ah,0   
    mov al,'$'
    call num_stk   
    mov ah,2
    call num_stk
    
    pop ax
    ret
no_digit endp          
   
end_pro proc
    mov ax,4c00h
    int 21h  
end_pro endp
;将输入的数字转成10进制并放入ax   
solve_num proc    
    call clean_screen
    cmp top,0 
    je solve_num_ret    
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
    je solve_num_ret        
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
    ;ax的值应小于等于100
    cmp ax,64h      
    ja out_range_10 
    cmp dx,0
    ja out_range_10 
    cmp ax,ax
    je solve_num_ret  

out_range_10:   
    mov bx,inNum
    mov ds,bx
    cmp in_n_count,3  
    jne solve_num_ret     
    call set_warn
    call out_range 
    jmp far to_get_num  
              
below_zero_10: 
    call set_warn
    call below_zero 
    jmp far to_get_num
    
solve_num_ret: 
    pop dx
    pop cx
    pop bx
    pop si
    pop ds
    ret                                                
solve_num endp
       
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

    mov ah,08h
    int 21h     
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
    
    mov ah,08h
    int 21h   
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
    mov is_warn,1 
    inc w_count
    cmp w_count,3 
    jne set_warn_ret
    call exit_show
set_warn_ret:               
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
    mov is_warn,0
    
    pop di
    pop ds
    pop ax    
    ret
cancel_warn endp    

;延迟时间  
delay proc      
    push cx
    mov cx,0ffffh
end_loop: 
    push cx
    mov cx,66h
end_loop_:       
    nop   
    loop end_loop_
    pop cx
    loop end_loop  
    pop cx
    ret  
delay endp
 
exit_show proc
    call clean_screen
    ;移动光标位置
    mov ah,02h
    mov bh,0
    mov dh,12
    mov dl,25
    int 10h          
    
    ;显示字符串       
    mov ax,warn
    mov ds,ax
    mov dx,offset w_end
    mov ah,09h
    int 21h     
    
    mov ax,0b800h
    mov ds,ax
    mov di,160*12+51
    mov cx,28
show_out4:
    mov ds:[di],11110100b
    inc di
    inc di
    loop show_out4 
    call delay 
    call clean_screen
    call end_pro
exit_show endp 
   
reset_16 proc   
    push bx
    push cx
    push ds
    push di   
    push es
    push si
    
    mov bx,radix_16_stk  
    mov ds,bx        
    mov bx,pre_data
    mov es,bx
    mov si,offset p_tmp_16
    mov di,offset tmp_16
    mov cx,9
reset_16_loop1:        
    mov bl,byte ptr es:[si]
    mov byte ptr [di],bl  
    inc di  
    inc si
    loop reset_16_loop1
    
    mov di,offset f1_16 
    mov si,offset p_f1_16
    mov cx,9
reset_16_loop2: 
    mov bl,byte ptr es:[si]
    mov byte ptr [di],bl    
    inc di  
    inc si
    loop reset_16_loop2
    
    mov di,offset f2_16  
    mov si,offset p_f2_16 
    mov cx,9
reset_16_loop3:
    mov bl,byte ptr es:[si]
    mov byte ptr [di],bl  
    inc di 
    inc si
    loop reset_16_loop3
    
    pop si
    pop es
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
    cmp fib_length,0
    ja short p_16_ok      
    pop ax
    pop bx
    pop es
    pop cx
    pop si
    pop di
    jmp far restart
p_16_ok:
    mov cx,fib_length
     
    call reset_16  
    
    mov bx,radix_16_stk  
    mov ds,bx  
    mov bx,0b800h 
    mov es,bx
    mov si,4
    mov bx,0    
final_loop_16:  
    push cx
    ;输出f2_16，并使得tmp=f2 f2=f1+f2 f1=tmp   
    mov ax,offset f2_16
    add ax,8
    mov di,ax
    mov cx,9  

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
    mov cx,9
swap_tmp_16:
    mov al,byte ptr [di]
    mov byte ptr [si],al
    inc di
    inc si
    loop swap_tmp_16   
    
    mov di,offset f1_16
    mov si,offset f2_16  
    mov cx,9    
    clc;清除进位
add_f2_16:
    mov al,byte ptr [di] 
    adc al,byte ptr [si] 
    pushf
    mov byte ptr [si],al   
    inc di
    inc si   
    popf
    loop add_f2_16 
    
    mov di,offset tmp_16
    mov si,offset f1_16
    mov cx,9
swap_f1_16:
    mov al,byte ptr [di]
    mov byte ptr [si],al
    inc di
    inc si
    loop swap_f1_16 
    
    pop si
    pop cx     
    inc bx
    cmp bx,4    
    jne ok2   
    add si,8  
    mov bx,0
ok2:
    loop final_loop_16       

16_ret:
    pop ax
    pop bx
    pop es
    pop cx
    pop si
    pop di
    ret
print_16 endp    
 
reset_10 proc
    push ax
    push ds
    push si
    push cx
    
    mov ax,pre_data
    mov ds,ax   
    lea si, p_tmp_10 
    mov ax,0
    mov cx,5
r_10_loop1: 
    mov ds:[si],ax 
    add si,2
    loop r_10_loop1  
    
    lea si, p_f1_10 
    mov ax,0
    mov cx,5
r_10_loop2: 
    mov ds:[si],ax 
    add si,2
    loop r_10_loop2  
    
    lea si, p_f2_10 
    mov ax,0
    mov cx,5
r_10_loop3: 
    mov ds:[si],ax  
    add si,2
    loop r_10_loop3
    
    pop cx
    pop si
    pop ds
    pop ax
    ret
reset_10 endp

change_radix proc  
    push ax
    push ds
    push si
    push di
    push bx
    push cx
    
    mov ax,pre_data
    mov ds,ax      
    
    mov cx,10      
    lea si,p_tmp_16
    lea di,p_tmp_10
    add bx,0 
c_r_loop1:     
    mov al,byte ptr [si]
    adc al,0
    daa            
    mov byte ptr [di],al    
    pushf
    inc si
    inc di
    popf
    loop c_r_loop1  
    
    mov cx,3      
    lea si,p_f1_16
    lea di,p_f1_10 
    mov ax,word ptr [si]
c_r_loop2: 
    mov dx,0 
    mov bx,10   
    div bx     
    mov bx,0
    mov bl,dl
    shl bx,4
    push bx  
    mov bx,10
    mov dx,0
    div bx 
    pop bx 
    mov bh,dl
    shr bx,4
    mov byte ptr [di],bl
    inc di
    loop c_r_loop2

    mov cx,3      
    lea si,p_f2_16
    lea di,p_f2_10 
    mov ax,word ptr [si]
c_r_loop3: 
    mov dx,0 
    mov bx,10   
    div bx     
    mov bx,0
    mov bl,dl
    shl bx,4
    push bx  
    mov bx,10
    mov dx,0
    div bx 
    pop bx 
    mov bh,dl
    shr bx,4
    mov byte ptr [di],bl
    inc di
    loop c_r_loop3
     
    pop cx
    pop bx
    pop di
    pop si
    pop ds
    pop ax
    ret
change_radix endp
  
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
    cmp fib_length,0
    ja short p_10_ok  
    pop ax
    pop bx
    pop es
    pop cx
    pop si
    pop di
    jmp far restart
p_10_ok:
    mov cx,fib_length
    
    mov bx,pre_data
    mov ds,bx
    mov bx,0b800h 
    mov es,bx
    mov si,4
    mov bx,0  
    call reset_10
    call change_radix
final_loop_10: 
    push bx
    push cx   
    
    mov ax,offset p_f2_10
    add ax,8     
    mov di,ax  
    mov cx,9  
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
    
    mov di,offset p_f2_10
    mov si,offset p_tmp_10  
    mov cx,9
swap_tmp_10:
    mov al,byte ptr [di]
    mov byte ptr [si],al 
    inc di
    inc si
    loop swap_tmp_10
    
    mov di,offset p_f1_10
    mov si,offset p_f2_10  
    mov cx,9
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
      
    mov di,offset p_tmp_10
    mov si,offset p_f1_10  
    mov cx,9
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
    cmp bx,4    
    jne ok3   
    add si,8  
    mov bx,0
ok3:
    loop final_loop_10 

10_ret:    
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
