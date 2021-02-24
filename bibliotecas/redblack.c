#include "redblack.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

no_arvore* new_no_arvore(Criptografia data) {
    no_arvore* n = malloc(sizeof(no_arvore));
    n->left = NULL;
    n->right = NULL;
    n->parent = NULL;
    n->data = data;
    n->color = true;
    return n;
}

arvore_vermelho_preto* new_arvore_vermelho_preto() {
    Criptografia a;
    a.palavraCriptografada = NULL;
    a.palavraReal = NULL;
    arvore_vermelho_preto *t = malloc(sizeof(arvore_vermelho_preto));
    no_arvore*nil_node = malloc(sizeof(no_arvore));
    nil_node->left = NULL;
    nil_node->right = NULL;
    nil_node->parent = NULL;
    nil_node->color = false;
    nil_node->data = a;
    t->NIL = nil_node;
    t->root = t->NIL;
    return t;
}

void left_rotate(arvore_vermelho_preto*t, no_arvore*x) {
    no_arvore*y = x->right;
    x->right = y->left;
    if(y->left != t->NIL) {
        y->left->parent = x;
    }
    y->parent = x->parent;
    
    if(x->parent == t->NIL) {
        t->root = y;
    }else if(x == x->parent->left) { 
        //x é o filho da esquerda
        x->parent->left = y;
    }else{ 
        //x é o filho da direita
        x->parent->right = y;
    }
    y->left = x;
    x->parent = y;
}

void right_rotate(arvore_vermelho_preto*t, no_arvore*x) {
    no_arvore*y = x->left;
    x->left = y->right;
    if(y->right != t->NIL) {
        y->right->parent = x;
    }
    y->parent = x->parent;
    if(x->parent == t->NIL) {
        t->root = y;
    }else if(x == x->parent->right) { 
        //x é o filho da esquerda
        x->parent->right = y;
    }else{
        //x é o filho da direita
        x->parent->left = y;
    }
    y->right = x;
    x->parent = y;
}

void insertion_fixup(arvore_vermelho_preto*t, no_arvore*z) {
    while(z->parent->color == true) {
        if(z->parent == z->parent->parent->left) {
            //z.parent é o filho da esquerda
            no_arvore*y = z->parent->parent->right;
            if(y->color == true) {
                z->parent->color = false;
                y->color = false;
                z->parent->parent->color = true;
                z = z->parent->parent;
            }
            else {
                if(z == z->parent->right) {
                    z = z->parent;
                    left_rotate(t, z);
                }
                z->parent->color = false;
                z->parent->parent->color = true;
                right_rotate(t, z->parent->parent);
            }
        }
        else { 
            //z.parent é o filho da direita
            no_arvore*y = z->parent->parent->left;

            if(y->color == true) {
                z->parent->color = false;
                y->color = false;
                z->parent->parent->color = true;
                z = z->parent->parent;
            }
            else {
                if(z == z->parent->left) {
                    z = z->parent;
                    right_rotate(t, z);
                }
                z->parent->color = false;
                z->parent->parent->color = true;
                left_rotate(t, z->parent->parent);
            }
        }
    }
    t->root->color = false;
}

void insert(arvore_vermelho_preto*t, no_arvore*z) {
    no_arvore* y = t->NIL;
    no_arvore* temp = t->root;
    int i = 0, esquerda=0, direita=0;

    while(temp != t->NIL) {
        i+=1;
        y = temp;
        if(strcmp(z->data.palavraReal,temp->data.palavraReal)<0){
        temp = temp->left;
        esquerda+=1;
        }else{
        temp = temp->right;
        direita+=1;
        }
    }
    z->parent = y;

    //criptografia
    char auxiliador;
    if(i%2==0){
        esquerda = -esquerda;
    }else{
        direita = -direita;
    }
    for(int j=0;j<strlen(z->data.palavraReal);j++){
        auxiliador = z->data.palavraReal[j];
        if(auxiliador == 'a' || auxiliador == 'e'|| auxiliador == 'i'|| auxiliador == 'o'|| auxiliador == 'u'){
        z->data.palavraCriptografada[j] = z->data.palavraReal[j]+direita;
        }else {
        z->data.palavraCriptografada[j] = z->data.palavraReal[j]+esquerda;
        }
    }

    if(y == t->NIL) {
        t->root = z;
    }
    else if(strcmp(z->data.palavraReal, y->data.palavraReal)<0)
        y->left = z;
    else
        y->right = z;

    z->right = t->NIL;
    z->left = t->NIL;

    insertion_fixup(t, z);
}

void rb_transplant(arvore_vermelho_preto*t, no_arvore*u, no_arvore*v) {
    if(u->parent == t->NIL)
        t->root = v;
    else if(u == u->parent->left)
        u->parent->left = v;
    else
        u->parent->right = v;
    v->parent = u->parent;
}

no_arvore* minimum(arvore_vermelho_preto*t, no_arvore*x) {
    while(x->left != t->NIL)
        x = x->left;
    return x;
}

void rb_delete_fixup(arvore_vermelho_preto*t, no_arvore*x) {
    while(x != t->root && x->color == false) {
        if(x == x->parent->left) {
        no_arvore*w = x->parent->right;
        if(w->color == true) {
            w->color = false;
            x->parent->color = true;
            left_rotate(t, x->parent);
            w = x->parent->right;
        }
        if(w->left->color == false && w->right->color == false) {
            w->color = true;
            x = x->parent;
        }
        else {
            if(w->right->color == false) {
            w->left->color = false;
            w->color = true;
            right_rotate(t, w);
            w = x->parent->right;
            }
            w->color = x->parent->color;
            x->parent->color = false;
            w->right->color = false;
            left_rotate(t, x->parent);
            x = t->root;
        }
        }
        else {
        no_arvore*w = x->parent->left;
        if(w->color == true) {
            w->color = false;
            x->parent->color = true;
            right_rotate(t, x->parent);
            w = x->parent->left;
        }
        if(w->right->color == false && w->left->color == false) {
            w->color = true;
            x = x->parent;
        }
        else {
            if(w->left->color == false) {
            w->right->color = false;
            w->color = true;
            left_rotate(t, w);
            w = x->parent->left;
            }
            w->color = x->parent->color;
            x->parent->color = false;
            w->left->color = false;
            right_rotate(t, x->parent);
            x = t->root;
        }
        }
    }
    x->color = false;
}

void rb_delete(arvore_vermelho_preto*t, no_arvore*z) {
    no_arvore*y = z;
    no_arvore*x;
    bool y_orignal_color = y->color;
    if(z->left == t->NIL) {
        x = z->right;
        rb_transplant(t, z, z->right);
    }
    else if(z->right == t->NIL) {
        x = z->left;
        rb_transplant(t, z, z->left);
    }
    else {
        y = minimum(t, z->right);
        y_orignal_color = y->color;
        x = y->right;
        if(y->parent == z) {
        x->parent = z;
        }
        else {
        rb_transplant(t, y, y->right);
        y->right = z->right;
        y->right->parent = y;
        }
        rb_transplant(t, z, y);
        y->left = z->left;
        y->left->parent = y;
        y->color = z->color;
    }
    if(y_orignal_color == false)
        rb_delete_fixup(t, x);
}

void inorder(arvore_vermelho_preto*t, no_arvore*n) {
    if(n != t->NIL) {
        inorder(t, n->left);
        printf("%d\n", n->data);
        inorder(t, n->right);
    }
}