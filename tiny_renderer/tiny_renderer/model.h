#ifndef __MODEL_H__
#define __MODEL_H__

#include "vector.h"
#include "geometry.h"
#include "tgaimage.h"


class Model {
private:
	m::vector<Vec3f> verts_;
	m::vector<m::vector<Vec3i> > faces_; // attention, this Vec3i means vertex/uv/normal
	m::vector<Vec3f> norms_;
	m::vector<Vec2f> uv_;
	TGAImage diffusemap_;
	void load_texture(std::string filename, const char *suffix, TGAImage &img);
public:
	Model(const char *filename);
	~Model();
	int nverts();
	int nfaces();
	Vec3f vert(int i);
	Vec2i uv(int iface, int nvert);
	TGAColor diffuse(Vec2i uv);
	m::vector<int> face(int idx);
};

#endif //__MODEL_H__
