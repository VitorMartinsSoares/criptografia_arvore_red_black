#ifndef REDBLACK_H
#define REDBLACK_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
typedef struct Criptografia{
    char *palavraReal;
    char *palavraCriptografada;
}Criptografia;

typedef struct no_arvore{
    Criptografia data;
    struct no_arvore*right;
    struct no_arvore*left;
    struct no_arvore*parent;
    bool color;
}no_arvore;

typedef struct arvore_vermelho_preto{
    no_arvore*root;
    no_arvore*NIL;
}arvore_vermelho_preto;

no_arvore* new_no_arvore(Criptografia data);
arvore_vermelho_preto* new_arvore_vermelho_preto();
void left_rotate(arvore_vermelho_preto*t, no_arvore*x);
void right_rotate(arvore_vermelho_preto*t, no_arvore*x);
void insertion_fixup(arvore_vermelho_preto*t, no_arvore*z);
void insert(arvore_vermelho_preto*t, no_arvore*z);
void rb_transplant(arvore_vermelho_preto*t, no_arvore*u, no_arvore*v);
no_arvore* minimum(arvore_vermelho_preto*t, no_arvore*x);
void rb_delete_fixup(arvore_vermelho_preto*t, no_arvore*x);
void rb_delete(arvore_vermelho_preto*t, no_arvore*z);
void inorder(arvore_vermelho_preto*t, no_arvore*n);

#endif