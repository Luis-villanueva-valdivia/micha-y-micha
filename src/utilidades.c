/*
 * Funcion:     limpiarBuffer
 * Descripcion: Descarta los caracteres que quedan en stdin hasta el fin
 *              de linea, para que una entrada invalida no afecte la
 *              siguiente lectura.
 * Parametros:  Ninguno.
 * Retorno:     Ninguno.
 */
void limpiarBuffer(void) {
    int c = 0;
    while ((c = getchar()) != '\n' && c != EOF) {
        /* Solo se descarta el caracter */
    }
}
