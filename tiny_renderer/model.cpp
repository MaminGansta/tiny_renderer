
//
//class Model {
//private:
//	m::vector<Vec3f> verts_;
//	m::vector<m::vector<Vec3i> > faces_; // attention, this Vec3i means vertex/uv/normal
//	m::vector<Vec3f> norms_;
//	m::vector<Vec2f> uv_;
//	TGAImage diffusemap_;
//	void load_texture(std::string filename, const char* suffix, TGAImage& img);
//public:
//	Model(const char* filename);
//	~Model();
//	int nverts();
//	int nfaces();
//	Vec3f vert(int i);
//	Vec2i uv(int iface, int nvert);
//	TGAColor diffuse(Vec2i uv);
//	m::vector<int> face(int idx);
//};
//
//#endif //__MODEL_H__
//
//
//Model::Model(const char *filename) : verts_(), faces_(), norms_(), uv_() {
//    std::ifstream in;
//    in.open (filename, std::ifstream::in);
//    if (in.fail()) return;
//    std::string line;
//    while (!in.eof()) {
//        std::getline(in, line);
//        std::istringstream iss(line.c_str());
//        char trash;
//        if (!line.compare(0, 2, "v ")) {
//            iss >> trash;
//            Vec3f v;
//            for (int i=0;i<3;i++) iss >> v[i];
//            verts_.push_back(v);
//        } else if (!line.compare(0, 3, "vn ")) {
//            iss >> trash >> trash;
//            Vec3f n;
//            for (int i=0;i<3;i++) iss >> n[i];
//            norms_.push_back(n);
//        } else if (!line.compare(0, 3, "vt ")) {
//            iss >> trash >> trash;
//            Vec2f uv;
//            for (int i=0;i<2;i++) iss >> uv[i];
//            uv_.push_back(uv);
//        }  else if (!line.compare(0, 2, "f ")) {
//            m::vector<Vec3i> f;
//            Vec3i tmp;
//            iss >> trash;
//            while (iss >> tmp[0] >> trash >> tmp[1] >> trash >> tmp[2]) {
//                for (int i=0; i<3; i++) tmp[i]--; // in wavefront obj all indices start at 1, not zero
//                f.push_back(tmp);
//            }
//            faces_.push_back(f);
//        }
//    }
//    std::cerr << "# v# " << verts_.size() << " f# "  << faces_.size() << " vt# " << uv_.size() << " vn# " << norms_.size() << std::endl;
//    load_texture(filename, "_diffuse.tga", diffusemap_);
//}
//
//Model::~Model() {
//}
//
//int Model::nverts() {
//    return (int)verts_.size();
//}
//
//int Model::nfaces() {
//    return (int)faces_.size();
//}
//
//m::vector<int> Model::face(int idx) {
//    m::vector<int> face;
//    for (int i=0; i<(int)faces_[idx].size(); i++) face.push_back(faces_[idx][i][0]);
//    return face;
//}
//
//Vec3f Model::vert(int i) {
//    return verts_[i];
//}
//
//void Model::load_texture(std::string filename, const char *suffix, TGAImage &img) {
//    std::string texfile(filename);
//    size_t dot = texfile.find_last_of(".");
//    if (dot!=std::string::npos) {
//        texfile = texfile.substr(0,dot) + std::string(suffix);
//        std::cerr << "texture file " << texfile << " loading " << (img.read_tga_file(texfile.c_str()) ? "ok" : "failed") << std::endl;
//        img.flip_vertically();
//    }
//}
//
//TGAColor Model::diffuse(Vec2i uv) {
//    return diffusemap_.get(uv.x, uv.y);
//}
//
//Vec2i Model::uv(int iface, int nvert) {
//    int idx = faces_[iface][nvert][1];
//    return Vec2i(uv_[idx].x*diffusemap_.get_width(), uv_[idx].y*diffusemap_.get_height());
//}


struct Model
{
private:
	std::vector<Vec3f> verts_;
	std::vector<std::vector<int[3]>> faces_; // attention, this Vec3i means vertex/uv/normal
	std::vector<Vec3f> norms_;
	std::vector<Vec2f> uv_;
	//TGAImage diffusemap_;

public:
	Model(const char* filename);
	~Model();
	int nverts();
	int nfaces();
	Vec3f vert(int i);
	Vec2i uv(int iface, int nvert);
	//TGAColor diffuse(Vec2i uv);
	std::vector<int> face(int idx);

	inline Model(char const* filename)
	{
		    std::ifstream in;
		    in.open (filename, std::ifstream::in);
		    if (in.fail()) return;
		    std::string line;
		    while (!in.eof()) {
		        std::getline(in, line);
		        std::istringstream iss(line.c_str());
		        char trash;
		        if (!line.compare(0, 2, "v ")) {
		            iss >> trash;
		            Vec3f v;
		            for (int i=0;i<3;i++) iss >> v[i];
		            verts_.push_back(v);
		        } else if (!line.compare(0, 3, "vn ")) {
		            iss >> trash >> trash;
		            Vec3f n;
		            for (int i=0;i<3;i++) iss >> n[i];
		            norms_.push_back(n);
		        } else if (!line.compare(0, 3, "vt ")) {
		            iss >> trash >> trash;
		            Vec2f uv;
		            for (int i=0;i<2;i++) iss >> uv[i];
		            uv_.push_back(uv);
		        }  else if (!line.compare(0, 2, "f ")) {
		            std::vector<int[3]> f;
		            int tmp[3];
		            iss >> trash;
		            while (iss >> tmp[0] >> trash >> tmp[1] >> trash >> tmp[2]) {
		                for (int i=0; i<3; i++) tmp[i]--; // in wavefront obj all indices start at 1, not zero
							f.push_back(tmp);
		            }
		            faces_.push_back(f);
		        }
		    }
		    std::cerr << "# v# " << verts_.size() << " f# "  << faces_.size() << " vt# " << uv_.size() << " vn# " << norms_.size() << std::endl;
		    //load_texture(filename, "_diffuse.tga", diffusemap_);
		
	}

	inline ~Model() {}
};