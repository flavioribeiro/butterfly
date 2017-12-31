#include "vireo/base_h.h"
#include "vireo/base_cpp.h"

#include "vireo/demux/movie.h"
//#include "vireo/decode/video.h"
//#include "vireo/encode/h264.h"
//#include "vireo/mux/mp4.h"
//#include "vireo/util/util.h"
//
#include "crow_all.h"

int main()
{
    crow::SimpleApp app;

    CROW_ROUTE(app, "/")([](){
        return "Hello w0rldzz!";
    });

    app.port(8080).multithreaded().run();
}

void transcode(std::string in, std::string out) {
  vireo::demux::Movie movie(in);
//  vireo::decode::Video decoder(movie.video_track);
//  vireo::encode::H264 encoder(decoder, 30.0f, 3, movie.video_track.fps());
//  vireo::mux::MP4 muxer(encoder);
//  auto binary = muxer();
//  vireo::util::save(out, binary);
}
