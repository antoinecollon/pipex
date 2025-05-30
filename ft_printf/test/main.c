#include "../ft_printf.h"
#include <stdio.h>
#include <limits.h>

int	main(void)
{
	int ret;
	int a = 42;

	ret = ft_printf("Char simple : [%c]\n", 'A');
	ft_printf("Retour : %d\n\n", ret);

	ret = ft_printf("Char invisible (null char) : [%c]\n", '\0');
	ft_printf("Retour : %d\n\n", ret);

	ret = ft_printf("String normale : [%s]\n", "Coucou");
	ft_printf("Retour : %d\n\n", ret);

	ret = ft_printf("String vide : [%s]\n", "");
	ft_printf("Retour : %d\n\n", ret);

	ret = ft_printf("String NULL : [%s]\n", NULL);
	ft_printf("Retour : %d\n\n", ret);

	ret = ft_printf("Entier positif : [%d]\n", 123);
	ft_printf("Retour : %d\n\n", ret);

	ret = ft_printf("Entier négatif : [%i]\n", -456);
	ft_printf("Retour : %d\n\n", ret);

	ret = ft_printf("INT_MIN : [%d]\n", INT_MIN);
	ft_printf("Retour : %d\n\n", ret);

	ret = ft_printf("Unsigned petit : [%u]\n", 42);
	ft_printf("Retour : %d\n\n", ret);

	ret = ft_printf("Unsigned grand : [%u]\n", 4000000000U);
	ft_printf("Retour : %d\n\n", ret);

	ret = ft_printf("Hexa minuscule : [%x]\n", 3735928559U);
	ft_printf("Retour : %d\n\n", ret);

	ret = ft_printf("Hexa majuscule : [%X]\n", 48879);
	ft_printf("Retour : %d\n\n", ret);

	ret = ft_printf("Hexa zéro : [%x]\n", 0);
	ft_printf("Retour : %d\n\n", ret);

	ret = ft_printf("Pointeur classique : [%p]\n", &a);
	ft_printf("Retour : %d\n\n", ret);

	ret = ft_printf("Pointeur NULL : [%p]\n", NULL);
	ft_printf("Retour : %d\n\n", ret);

	ret = ft_printf("Affichage de %% : [%%]\n");
	ft_printf("Retour : %d\n\n", ret);

	// 🧪 TEST ADDITIONNEL : comparaison double pointeur NULL
	int	ret1 = printf(" %p %p \n", (void *)0, (void *)0);
	int	ret2 = ft_printf(" %p %p \n", (void *)0, (void *)0);
	printf("printf    => %d caractères\n", ret1);
	printf("ft_printf => %d caractères\n\n", ret2);

	// Comparaison (ne surtout pas passer NULL en vrai printf)
	printf("⛳ Comparaison : [%d] [%s] [%p] [%%%c]\n", INT_MIN, "(null)", (void *)&a, '!');

	return (0);
}

