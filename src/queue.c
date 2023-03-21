/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   queue.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arabenst <arabenst@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 15:54:01 by arabenst          #+#    #+#             */
/*   Updated: 2023/03/21 12:46:18 by arabenst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	ft_op_to_queue(t_push_swap *data, char op)
{
	static size_t	i;
	char			*temp;

	if (i == data->q_size)
	{
		data->q_size *= 2;
		temp = ft_calloc(data->q_size + 1, sizeof(char));
		if (!temp)
			ft_exit(data, 1);
		ft_strlcpy(temp, data->queue, data->q_size + 1);
		free(data->queue);
		data->queue = temp;
	}
	data->queue[i++] = op;
}

void	print_op(char op)
{
	if (op & SWAP)
		ft_printf("s%c\n", 'a' + !!(op & B) + 17 * !!(op & A && op & B));
	else if (op & PUSH)
		ft_printf("p%c\n", 'a' + !!(op & B));
	else if (op & ROT)
		ft_printf("r%c\n", 'a' + !!(op & B) + 16 * !!(op & A && op & B));
	else if (op & REV)
		ft_printf("rr%c\n", 'a' + !!(op & B) + 16 * !!(op & A && op & B));
}

void	ft_clean_swaps(char *queue, int i, int count[2])
{
	if (count[A - 1] % 2 && count[B - 1] % 2)
		queue[i] = SWAP | A | B;
	else if (count[A - 1] % 2)
		queue[i] = SWAP | A;
	else if (count[B - 1] % 2)
		queue[i] = SWAP | B;
}

void	ft_clean_rotate(char *queue, int action, int i, int count[2])
{
	int	j;

	j = i;
	while (j - i < (count[A - 1] * (count[A - 1] <= count[B - 1])
			+ count[B - 1] * (count[B - 1] < count[A - 1])))
		queue[j++] = action | A | B;
	while (j - i < count[A - 1])
		queue[j++] = action | A;
	while (j - i < count[B - 1])
		queue[j++] = action | B;
}

void	ft_clean_multiples(char *queue, char action, int i)
{
	int	j;
	int	count[2];

	count[A - 1] = 0;
	count[B - 1] = 0;
	j = i - 1;
	while (queue[++j] & action)
	{
		if ((queue[j] ^ action) & A)
			count[A - 1]++;
		if ((queue[j] ^ action) & B)
			count[B - 1]++;
		queue[j] = queue[j] ^ action;
	}
	if (action & SWAP)
		ft_clean_swaps(queue, i, count);
	else if ((action & ROT) || (action & REV))
		ft_clean_rotate(queue, action, i, count);
}

void	ft_clean_mixed(char *queue, int i)
{
	// pb
	// pb
	// sa
	// ra
	// sb
	// rra
	// pa
	// pa
	// rra
	// rra
	(void)queue;
	(void)i;
}

void	ft_optimize_queue(t_push_swap *data)
{
	int	i;

	i = -1;
	while (data->queue[++i])
	{
		ft_clean_multiples(data->queue, SWAP, i);
		ft_clean_multiples(data->queue, ROT, i);
		ft_clean_multiples(data->queue, REV, i);
		ft_clean_mixed(data->queue, i);
	}
}

void	ft_print_queue(t_push_swap *data)
{
	int		i;
	char	op;

	i = -1;
	while (data->queue[++i])
	{
		op = data->queue[i];
		if (op & SWAP)
			ft_printf("s%c\n", 'a' + !!(op & B) + 17 * !!(op & A && op & B));
		else if (op & PUSH)
			ft_printf("p%c\n", 'a' + !!(op & B));
		else if (op & ROT)
			ft_printf("r%c\n", 'a' + !!(op & B) + 16 * !!(op & A && op & B));
		else if (op & REV)
			ft_printf("rr%c\n", 'a' + !!(op & B) + 16 * !!(op & A && op & B));
	}
}


/* ************************************************************************** */
/*                                  CRASHES                                   */
/* ************************************************************************** */
// 400 177 250 74 161 483 208 170 338 13 249 497 448 308 382 179 316 251 138 55 101 126 165 125 459 461 365 373 292 191 200 234 204 60 422 379 345 482 253 286 39 215 280 432 181 29 274 5 444 452 173 241 311 358 62 299 178 240 457 499 349 442 103 69 111 489 490 245 424 174 454 378 322 381 202 219 329 430 27 205 389 425 146 313 260 376 332 76 130 17 112 341 213 285 258 57 32 44 470 254 317 153 230 186 203 237 440 98 140 481 199 108 96 3 88 333 403 340 133 159 402 356 16 300 169 303 226 385 412 190 43 9 71 145 209 420 48 347 242 361 198 14 336 236 354 4 49 375 404 35 182 120 302 476 321 487 468 326 151 247 229 451 164 473 72 270 407 110 346 235 447 276 24 390 257 312 40 456 467 50 18 331 339 194 284 498 12 239 58 56 343 256 491 466 328 301 83 183 233 264 396 37 291 370 469 267 86 275 114 495 121 20 391 268 149 388 197 30 418 134 334 156 148 106 192 465 238 386 93 394 104 81 150 102 263 261 162 193 184 107 78 38 132 255 97 463 453 80 323 392 51 395 475 232 85 196 273 99 353 105 355 306 409 401 113 423 171 84 206 246 496 142 458 384 180 122 283 220 445 439 480 474 141 455 296 63 47 269 369 500 478 428 298 486 70 488 46 393 436 304 377 95 479 415 175 172 210 136 414 68 318 147 471 92 94 426 45 295 372 15 21 163 421 2 410 139 314 287 31 195 10 127 427 166 67 324 109 19 406 221 207 433 214 289 124 152 131 217 344 380 259 293 22 435 115 201 460 294 485 225 477 337 8 61 366 100 363 383 23 66 228 357 265 158 244 7 288 185 41 160 59 434 79 211 6 362 438 441 464 315 1 408 342 367 405 90 297 446 53 65 282 36 117 484 472 277 327 82 218 307 52 118 399 176 310 411 374 330 279 419 143 91 26 34 449 144 167 335 231 290 368 188 437 319 223 272 128 443 137 25 89 157 75 224 135 154 155 243 364 123 387 227 352 212 187 462 281 493 360 371 309 87 266 262 129 398 33 417 492 248 397 216 351 73 54 168 77 494 450 413 271 278 64 42 189 222 431 28 416 252 350 325 359 320 429 119 305 348 11 116 