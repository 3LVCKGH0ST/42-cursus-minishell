/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asouinia <asouinia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/25 22:25:58 by asouinia          #+#    #+#             */
/*   Updated: 2022/03/25 22:31:35 by asouinia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKEN_H
# define TOKEN_H

typedef enum e_token {
	TOKEN_LBRACE	//? <>
	TOKEN_RBRACE	//? <>
	TOKEN_OR,		//? <>
	TOKEN_AND,		//? <>
	TOKEN_PIPE,		//? <>
	TOKEN_RIN,		//? <>
	TOKEN_ROUT,		//? <>
	TOKEN_DRIN,		//? <>
	TOKEN_DROUT		//? <>
	TOKEN_SQUOTE	//? <>
	TOKEN_DQUOTE	//? <>
	TOKEN_EOF,		//? <>
}	t_e_token;		//? <>

typedef struct s_token
{
	char		*value;
	t_e_token	type;
}	t_token;
#endif
