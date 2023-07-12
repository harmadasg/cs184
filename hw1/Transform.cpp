// Transform.cpp: implementation of the Transform class.

#include "Transform.h"

//Please implement the following functions:

// Helper rotation function.  
mat3 Transform::rotate(const float degrees, const vec3& axis) {
  float cosine = cos(glm::radians(degrees));
  float sine = sin(glm::radians(degrees));

  vec3 normalized_axis = glm::normalize(axis);
  float x = normalized_axis.x;
  float y = normalized_axis.y;
  float z = normalized_axis.z;

  mat3 unchanged_component = mat3(cosine);
  mat3 parallel_component = mat3(x*x, x*y, x*z, x*y, y*y, y*z, x*z, y*z, z*z) * (1 - cosine);
  mat3 perpendicular_component = mat3(0, z, -y, -z, 0, x, y, -x, 0) * sine;

  return unchanged_component + parallel_component + perpendicular_component;
}

// Transforms the camera left around the "crystal ball" interface
void Transform::left(float degrees, vec3& eye, vec3& up) {
  mat3 rotation_matrix = rotate(degrees, up);
  eye = rotation_matrix * eye;
  up = rotation_matrix * up;
}

// Transforms the camera up around the "crystal ball" interface
void Transform::up(float degrees, vec3& eye, vec3& up) {
  vec3 axis = glm::cross(eye, up);
  mat3 rotation_matrix = rotate(degrees, axis);
  eye = rotation_matrix * eye;
  up = rotation_matrix * up;
}

// Your implementation of the glm::lookAt matrix
mat4 Transform::lookAt(vec3 eye, vec3 up) {
  vec3 w = glm::normalize(eye);
  vec3 u = glm::normalize(glm::cross(up, w));
  vec3 v = glm::cross(w, u);

  return mat4(
    u.x, u.y, u.z, glm::dot(u, -eye),
    v.x, v.y, v.z, glm::dot(v, -eye),
    w.x, w.y, w.z, glm::dot(w, -eye),
    0, 0, 0, 1
  );
}

Transform::Transform()
{

}

Transform::~Transform()
{

}
