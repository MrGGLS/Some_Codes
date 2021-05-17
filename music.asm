; 1     2   3   4   5   6   7 
;                           123 lower
;138    147 165 175 196 220 247 low
;262    294 330 349 392 440 494 medi
;524    587 659 698 784 880 988 high    
;音乐数据
data segment
;数字曲谱
freq dw 220,262,392,262,175,196,220,392,262
     dw 138,196,392,262,138,392,123,392
     dw 220,262,392,262,175,196,220,392,262
     dw 138,196,392,262,138,392,123,262,392 
     dw 220,262,392,262,175,196,220,392,262
     dw 138,196,392,262,138,392,123,392
     dw 220,262,392,262,175,196,220,392,262
     dw 138,196,392,262,138,392,123,262,392,-1

;单个音符的持续时间
time dw 12,12,12,12,12,6,6,12,12
     dw 12,12,12,12,12,12,12,12
     dw 12,12,12,12,12,6,6,12,12
     dw 12,12,12,12,12,12,6,6,12  
     dw 12,12,12,12,12,6,6,12,12
     dw 12,12,12,12,12,12,12,12
     dw 12,12,12,12,12,6,6,12,12
     dw 12,12,12,12,12,12,6,6,12
data ends
;开场提示界面
welcome segment
    wel db 'Welcome to my music player','$';length=26
    pre db 'Press any key to play.....','$';length=26 
    end_w db 'THANK YOU FOR YOUR LISTENING!','$';length=29
welcome ends
;栈空间
stk segment
    db 200h dup(0)
stk ends
            
;动画效果所需变量
for_anime segment
    count dw 0 
    p_freq dw 0 
    h_len dw 80  
    v_len dw 25      
for_anime ends
                
code segment
start:
    mov ax,stk
    mov ss,ax
    mov sp,100h
    mov ax,data
    mov ds,ax
    lea si,freq
    lea di,time 
    
    call clean_screen
    call welcome_   
      
    mov ah,07h
    int 21h    
    
play:
    mov dx,[si]
    cmp dx,-1
    je end_play
    call sound
    add si,2
    add di,2
    jmp play
end_play: 
    call clean_screen  
    call end_anime
    
    mov ah,07h
    int 21h          
    
    call clean_screen   
    
    mov ax,4c00h
    int 21h
    ;演奏一个音符   
    
sound proc
    push ax
    push dx
    push cx      
              
    call anime;//动画效果，随时间而变... 
    
    mov al,0b6h
    out 43h,al
    mov dx,12h
    mov ax,34dch
    div word ptr [si]
    out 42h,al
    mov al,ah
    out 42h,al
    in al,61h
    mov ah,al
    or al,3
    out 61h,al
    mov dx,[di]
    or al,3
    out 61h,al
    mov dx,[di]
continue:
    mov cx,0efffh
delay:
    nop
    loop delay
    dec dx
    jnz continue
    ;恢复扬声器原值
    mov al,ah
    out 61h,al  
    
    pop cx
    pop dx
    pop ax
    ret  
sound endp

clean_screen proc             
    push ax
    mov  ah,0fh
    int  10h
    mov  ah,0
    int  10h  
    pop ax
    ret       
clean_screen endp 

welcome_ proc     
    push ax
    push bx
    push dx
    push ds
    push cx
    push di
    
    ;转移光标位置
    mov ah,02h
    mov bh,0
    mov dh,12
    mov dl,40-13
    int 10h
             
    ;显示字符串
    mov ax,welcome
    mov ds,ax
    mov dx,0h
    mov ah,09h 
    int 21h 
    
    mov ax,0b800h
    mov ds,ax
    mov di,160*12+80-25
    mov cx,26
show_w1:
    mov ds:[di],11110010b
    inc di
    inc di
    loop show_w1 
    
    ;转移光标位置
    mov ah,02h
    mov bh,0
    mov dh,13
    mov dl,40-13
    int 10h
             
    ;显示字符串
    mov ax,welcome
    mov ds,ax
    mov dx,offset pre
    mov ah,09h 
    int 21h 
    
    mov ax,0b800h
    mov ds,ax
    mov di,160*13+80-25
    mov cx,26
show_w2:
    mov ds:[di],11110010b
    inc di
    inc di
    loop show_w2            
    
    pop di
    pop cx
    pop ds
    pop dx
    pop bx
    pop ax
    ret
welcome_ endp  
 
anime proc    
    push ax
    push ds
    push bx
    push es
    push si
    push cx
    push dx
    
    call clean_screen  
           
    ;画矩形  
    mov ax,for_anime
    mov ds,ax 
    mov bx,0b800h
    mov es,bx 
    
    call draw_rec  
    add al,22
    
    ;画上边  
    mov bx,h_len  
    mov si,0
    mov cx,count  
    cmp cx,0
    je done1 
loop1:
    sub bx,8
    add si,8   
    add si,160*2
    add ah,2
    loop loop1   
done1:
    mov cx,bx    
    mov dx,bx
draw_up:              
    cmp cx,dx
    jne ok1
    call draw_left
ok1:
    cmp cx,1
    jne ok2
    call draw_right    
ok2:              
    mov byte ptr es:[si],al
    mov byte ptr es:[si+1],ah   
    add si,2
    loop draw_up 
    
    ;画下边
    mov bx,h_len  
    mov si,160*24
    mov cx,count   
    cmp cx,0
    je done2
loop2:
    sub bx,8
    add si,8   
    sub si,160*2
    loop loop2  
done2:
    mov cx,bx    
draw_down: 
    mov byte ptr es:[si],al
    mov byte ptr es:[si+1],ah 
    add si,2
    loop draw_down 
    
    inc count   
    cmp count,3
    jne anime_ret
    mov count,0
anime_ret:   
    pop dx
    pop cx
    pop si 
    pop es
    pop bx
    pop ds
    pop ax
    ret    
anime endp
  
draw_left proc    
    push cx
    push bx
    push si
    
    mov cx,count     
    mov bx,v_len  
    cmp cx,0
    je done3
loop3:
    sub bx,4
    loop loop3  
done3:
    mov cx,bx
_draw_left: 
    mov byte ptr es:[si],al
    mov byte ptr es:[si+1],ah  
    add si,160
    loop _draw_left
    
    pop si
    pop bx
    pop cx
    ret
draw_left endp
  
draw_right proc 
    push cx
    push bx
    push si
    
    mov cx,count 
    mov bx,v_len  
    cmp cx,0
    je done4
loop4:
    sub bx,4
    loop loop4  
done4:
    mov cx,bx
_draw_right:
    mov byte ptr es:[si],al
    mov byte ptr es:[si+1],ah
    add si,160
    loop _draw_right
     
    pop si
    pop bx
    pop cx
    ret
draw_right endp
  
draw_rec proc
    push di
    push bx
    push ds
    push cx
    push es
    push si 
     
    mov di,p_freq 
    inc p_freq
    mov bx,data
    mov ds,bx
    mov bx,[di]
    
    mov cx,8
    cmp bx,0
    ja next1
    dec cx 
next1:
    cmp bx,50
    ja next2
    dec cx
next2:         
    cmp bx,100
    ja next3
    dec cx
next3: 
    cmp bx,150
    ja next4
    dec cx
next4: 
    cmp bx,200
    ja next5
    dec cx
next5: 
    cmp bx,250
    ja next6
    dec cx
next6:
    cmp bx,300
    ja next7
    dec cx
next7: 
    cmp bx,350
    ja next8
    dec cx
next8:
    cmp cx,0
    jbe draw_rec_ret  
    mov al,'-'
    mov ah,00000000b
    mov bx,cx
change_ax:     
    dec al
    add ah,00000001b
    loop change_ax   
    
    mov cx,bx
    mov bx,0b800h
    mov es,bx
    mov si,16*160+36*2
_draw_rec:
    push cx
    mov cx,8
__draw_rec:
    mov byte ptr es:[si],al
    mov byte ptr es:[si+1],ah 
    add si,2
    loop __draw_rec
    pop cx
    sub si,16 
    sub si,160
    loop _draw_rec

draw_rec_ret:
    pop si
    pop es
    pop cx
    pop ds
    pop bx
    pop di
    ret               
draw_rec endp  

end_anime proc  
    push ax
    push ds
    push di
    push es
    push si
             
    ;显示字符串
    mov ax,welcome
    mov ds,ax
    mov di,offset end_w
    
    mov ax,0b800h
    mov es,ax
    mov si,160*12+80-30
    mov cx,29
show_end:                
    mov al,byte ptr ds:[di]
    mov byte ptr es:[si],al
    mov byte ptr es:[si+1],01111101b
    inc di
    add si,2   
    call end_delay
    loop show_end 
    
    pop si
    pop es
    pop di
    pop ds
    pop ax
    ret
end_anime endp
  
end_delay proc      
    push cx
    mov cx,0ffffh
end_loop: 
    push cx
    mov cx,2
end_loop_:       
    nop   
    loop end_loop_
    pop cx
    loop end_loop  
    pop cx
    ret  
end_delay endp
   
code ends
end start

