/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   testing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nanasser <nanasser@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/24 15:24:09 by mtangalv          #+#    #+#             */
/*   Updated: 2026/02/23 23:10:18 by nanasser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"
#include "../includes/testing.h"

t_projectile	tick(t_environment *env, t_projectile *proj)
{
	t_projectile	new_proj;

	new_proj.position = add_tuples(proj->position, proj->velocity);
	new_proj.velocity = add_tuples(proj->velocity,
			env->gravity);
	new_proj.velocity = add_tuples(new_proj.velocity,
			env->wind);
	return (new_proj);
}

void	print_tuple(t_tuple t)
{
	printf("(%f, %f, %f, %f)\n", t.x, t.y, t.z, t.w);
}

void	print_matrix4(t_matrix4 matrix)
{
	int	i;
	int	j;

	i = 0;
	while (i < 4)
	{
		j = 0;
		while (j < 4)
			printf("%.5f ", matrix.data[i][j++]);
		printf("\n");
		i++;
	}
}

void	print_matrix3(t_matrix3 matrix)
{
	int	i;
	int	j;

	i = 0;
	while (i < 3)
	{
		j = 0;
		while (j < 3)
			printf("%f ", matrix.data[i][j++]);
		printf("\n");
		i++;
	}
}

// ============================================================================
// MATRIX4 TESTING SYSTEM
// ============================================================================

static void	test_matrix_creation(void)
{
	// t_matrix4	m;
	t_matrix4	identity;

	printf("\n[TEST] Matrix Creation\n");
	// m = create_matrix4();
	printf("  ✓ Created empty matrix4\n");
	
	identity = create_identity();
	printf("  ✓ Created identity matrix4\n");
	if (identity.data[0][0] == 1 && identity.data[1][1] == 1 
		&& identity.data[2][2] == 1 && identity.data[3][3] == 1)
		printf("  ✓ Identity matrix values correct\n");
	else
		printf("  ✗ Identity matrix values incorrect\n");
}

static void	test_matrix_equality(void)
{
	t_matrix4	m1;
	t_matrix4	m2;
	t_tuple		row[4];

	printf("\n[TEST] Matrix Equality\n");
	m1 = create_identity();
	m2 = create_identity();
	if (matrix4_equal(m1, m2))
		printf("  ✓ Equal identity matrices recognized\n");
	else
		printf("  ✗ Equal matrices not recognized\n");

	row[0] = create_tuple(1, 2, 3, 4);
	row[1] = create_tuple(5.5f, 6.5f, 7.5f, 8.5f);
	row[2] = create_tuple(9, 10, 11, 12);
	row[3] = create_tuple(13.5f, 14.5f, 15.5f, 16.5f);
	fill_matrix4(&m1, row);
	
	row[0] = create_tuple(1, 2, 3, 4);
	row[1] = create_tuple(5.5f, 6.5f, 7.5f, 8.5f);
	row[2] = create_tuple(9, 10, 11, 12);
	row[3] = create_tuple(13.5f, 14.5f, 15.5f, 16.5f);
	fill_matrix4(&m2, row);
	if (matrix4_equal(m1, m2))
		printf("  ✓ Custom matrices with equal values recognized\n");
	else
		printf("  ✗ Custom matrices with equal values NOT recognized\n");
}

static void	test_matrix_transpose(void)
{
	t_matrix4	m;
	t_matrix4	transposed;
	t_tuple		row[4];

	printf("\n[TEST] Matrix Transpose\n");
	row[0] = create_tuple(0, 9, 3, 0);
	row[1] = create_tuple(9, 8, 0, 0);
	row[2] = create_tuple(1, 8, 5, 3);
	row[3] = create_tuple(0, 0, 5, 8);
	fill_matrix4(&m, row);
	transposed = transpose_matrix4(m);
	
	if (transposed.data[0][1] == 9 && transposed.data[1][0] == 9)
		printf("  ✓ Matrix transpose successful (swapped positions)\n");
	else
		printf("  ✗ Matrix transpose failed\n");

	transposed = transpose_matrix4(create_identity());
	if (matrix4_equal(transposed, create_identity()))
		printf("  ✓ Identity matrix transpose equals identity\n");
	else
		printf("  ✗ Identity matrix transpose incorrect\n");
}

static void	test_matrix_multiplication(void)
{
	t_matrix4	a;
	t_matrix4	b;
	t_matrix4	c;
	t_tuple		row[4];

	printf("\n[TEST] Matrix Multiplication\n");
	
	row[0] = create_tuple(1, 2, 3, 4);
	row[1] = create_tuple(5, 6, 7, 8);
	row[2] = create_tuple(9, 8, 7, 6);
	row[3] = create_tuple(5, 4, 3, 2);
	fill_matrix4(&a, row);

	row[0] = create_tuple(-2, 1, 2, 3);
	row[1] = create_tuple(3, 2, 1, -1);
	row[2] = create_tuple(0, 1, 1, 2);
	row[3] = create_tuple(1, 1, 1, 1);
	fill_matrix4(&b, row);

	c = matrix_multiply(a, b);
	if (c.data[0][0] == 8 && c.data[0][1] == 12 && c.data[0][2] == 11 && c.data[0][3] == 11)
		printf("  ✓ Matrix-matrix multiplication correct\n");
	else
		printf("  ✗ Matrix-matrix multiplication incorrect (got [%.0f, %.0f, %.0f, %.0f])\n",
			c.data[0][0], c.data[0][1], c.data[0][2], c.data[0][3]);

	c = matrix_multiply(a, create_identity());
	if (matrix4_equal(c, a))
		printf("  ✓ Multiplying by identity returns original matrix\n");
	else
		printf("  ✗ Identity multiplication failed\n");
}

static void	test_matrix_tuple_multiply(void)
{
	t_matrix4	m;
	t_tuple		t;
	t_tuple		result;
	t_tuple		row[4];

	printf("\n[TEST] Matrix-Tuple Multiplication\n");
	
	row[0] = create_tuple(1, 2, 3, 4);
	row[1] = create_tuple(2, 4, 4, 2);
	row[2] = create_tuple(8, 6, 4, 1);
	row[3] = create_tuple(0, 0, 0, 1);
	fill_matrix4(&m, row);

	t = create_tuple(1, 2, 3, 1);
	result = matrix4_tuple_multiply(m, t);
	
	if (result.x == 18 && result.y == 24 && result.z == 33 && result.w == 1)
		printf("  ✓ Matrix-tuple multiplication correct\n");
	else
		printf("  ✗ Matrix-tuple multiplication incorrect (got [%.0f, %.0f, %.0f, %.0f])\n",
			result.x, result.y, result.z, result.w);

	result = matrix4_tuple_multiply(create_identity(), t);
	if (result.x == t.x && result.y == t.y && result.z == t.z && result.w == t.w)
		printf("  ✓ Identity-tuple multiplication returns original tuple\n");
	else
		printf("  ✗ Identity-tuple multiplication failed\n");
}

static void	test_transformations(void)
{
	t_matrix4	transform;
	t_tuple		p;
	t_tuple		result;

	printf("\n[TEST] Transformations (Translation, Scaling, Rotation)\n");

	// Translation test
	transform = translation(5, -3, 2);
	p = create_point(-3, 4, 5);
	result = matrix4_tuple_multiply(transform, p);
	if (fabs(result.x - 2) < 0.0001f && fabs(result.y - 1) < 0.0001f 
		&& fabs(result.z - 7) < 0.0001f)
		printf("  ✓ Translation of point works correctly\n");
	else
		printf("  ✗ Translation failed\n");

	// Scaling test
	transform = scaling(2, 3, 4);
	p = create_point(-4, 6, 8);
	result = matrix4_tuple_multiply(transform, p);
	if (fabs(result.x - (-8)) < 0.0001f && fabs(result.y - 18) < 0.0001f 
		&& fabs(result.z - 32) < 0.0001f)
		printf("  ✓ Scaling of point works correctly\n");
	else
		printf("  ✗ Scaling failed\n");

	// Rotation X test
	transform = rotation_x(M_PI / 4);
	p = create_point(0, 1, 0);
	result = matrix4_tuple_multiply(transform, p);
	if (fabs(result.x - 0) < 0.0001f && fabs(result.y - (sqrtf(2.0f)/2.0f)) < 0.0001f 
		&& fabs(result.z - (sqrtf(2.0f)/2.0f)) < 0.0001f)
		printf("  ✓ Rotation X works correctly\n");
	else
		printf("  ✗ Rotation X failed\n");

	// Rotation Y test
	transform = rotation_y(M_PI / 4);
	p = create_point(0, 0, 1);
	result = matrix4_tuple_multiply(transform, p);
	if (fabs(result.x - (sqrtf(2.0f)/2.0f)) < 0.0001f && fabs(result.y - 0) < 0.0001f 
		&& fabs(result.z - (sqrtf(2.0f)/2.0f)) < 0.0001f)
		printf("  ✓ Rotation Y works correctly\n");
	else
		printf("  ✗ Rotation Y failed\n");

	// Rotation Z test
	transform = rotation_z(M_PI / 4);
	p = create_point(0, 1, 0);
	result = matrix4_tuple_multiply(transform, p);
	if (fabs(result.x - (-(sqrtf(2.0f)/2.0f))) < 0.0001f && fabs(result.y - (sqrtf(2.0f)/2.0f)) < 0.0001f 
		&& fabs(result.z - 0) < 0.0001f)
		printf("  ✓ Rotation Z works correctly\n");
	else
		printf("  ✗ Rotation Z failed\n");
}

static void	test_determinant_inversion(void)
{
	t_matrix4	m;
	t_matrix4	inverted;
	t_matrix4	identity;
	t_tuple		row[4];
	float		det;

	printf("\n[TEST] Determinant and Inversion\n");

	row[0] = create_tuple(-2, -8, 3, 5);
	row[1] = create_tuple(-3, 1, 7, 3);
	row[2] = create_tuple(1, 2, -9, 6);
	row[3] = create_tuple(-6, 7, 7, -9);
	fill_matrix4(&m, row);

	det = determinant_4x4(m);
	printf("  ✓ Determinant calculated: %.5f\n", det);

	if (is_invertible(m))
		printf("  ✓ Matrix is recognized as invertible\n");
	else
		printf("  ✗ Matrix should be invertible\n");

	inverted = invert_4x4(m);
	identity = matrix_multiply(m, inverted);
	if (matrix4_equal(identity, create_identity()))
		printf("  ✓ M * M^-1 = Identity (inversion correct)\n");
	else
		printf("  ✗ Inversion resulted in non-identity product\n");
}

void	test_matrix4_system(void)
{
	printf("\n");
	printf("╔════════════════════════════════════════════════════════╗\n");
	printf("║          MATRIX4 SYSTEM TEST SUITE                     ║\n");
	printf("╚════════════════════════════════════════════════════════╝\n");

	test_matrix_creation();
	test_matrix_equality();
	test_matrix_transpose();
	test_matrix_multiplication();
	test_matrix_tuple_multiply();
	test_transformations();
	test_determinant_inversion();

	printf("\n");
	printf("╔════════════════════════════════════════════════════════╗\n");
	printf("║              TESTS COMPLETED                           ║\n");
	printf("╚════════════════════════════════════════════════════════╝\n");
	printf("\n");
}

void render_sphere_projection(t_canvas *canvas, t_world *world)
{
	t_tuple ray_origin;
	float wall_z;
	float wall_width;
	float wall_height;
	float pixel_size_x;
	float pixel_size_y;
	float half_width;
	float half_height;
	t_intersection_list *xs;
	t_intersection h;
	t_tuple wall_point;
	t_ray ray;
	float world_x;
	float world_y;
	int x;
	int y;

	new_world(world);
	ray_origin = world->sp->position;
	wall_z = 10.0f;
	wall_height = 7.0f;
	wall_width = wall_height * ((float)WIN_WIDTH / (float)WIN_HEIGHT);
	pixel_size_x = wall_width / WIN_WIDTH;
	pixel_size_y = wall_height / WIN_HEIGHT;
	half_width = wall_width / 2.0f;
	half_height = wall_height / 2.0f;
	

	y = 0;
	while (y < WIN_HEIGHT)
	{
		world_y = half_height - pixel_size_y * (y + 0.5f);
		x = 0;
		while (x < WIN_WIDTH)
		{
			world_x = -half_width + pixel_size_x * (x + 0.5f);
			wall_point = create_point(world_x, world_y, wall_z);
			ray = create_ray(ray_origin, sub_tuples(wall_point, ray_origin));
			xs = intersect_sphere(ray, world->sp);
			if (xs)
			{
				h = hit(xs);
				if (h.object)
				{
					// 1. find the hit point in world space
					t_tuple hit_point = position(ray, h.t);
					// 2. find the normal at the hit
					t_tuple normalv = normal_at(h.object, hit_point);
					// 3. eye vector is the negated ray direction
					t_tuple eyev = negate_tuple(ray.dir);
					// 4. build lighting context and shade
					world->l->light.material = world->sp->material;
					world->l->light.h_position = hit_point;
					world->l->light.normalv = normalv;
					world->l->light.eyev = eyev;
					t_color color = lighting(&world->l->light);
					write_pixel(canvas, x, y, color);
				}
				free(xs->items);
				free(xs);
			}
			x++;
		}
		y++;
	}
}
