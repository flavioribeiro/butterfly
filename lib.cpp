#include "vireo/base_h.h"
#include "vireo/base_cpp.h"
#include "vireo/demux/movie.h"

#include "lib.h"
#include "crow_all.h"

using namespace std;

bool is_request_valid(const crow::request& req) {
  return req.url_params.get("bitrate") != nullptr &&
    req.url_params.get("width") != nullptr && 
    req.url_params.get("height") != nullptr;
}

stringstream transcode(VideoChunk chunk) {
  stringstream transcoded_chunk;

//  vireo::demux::Movie movie(chunk.filename);
  transcoded_chunk << "ok" << chunk.bitrate;
  return transcoded_chunk;
}

// chunk function
//demux::Movie movie(s_src.str());
//if (movie.video_track.count()) {  // Video
//  // setup mp4 encoder
//  unique_ptr<mux::MP4> mp4_encoder;
//  auto write_chunk = [&](uint32_t index, uint64_t start_pts, uint64_t end_pts){
//    cout << index << ".mp4 (start time: " << (float)start_pts / movie.video_track.settings().timescale << "s, ";
//    cout << "duration: " << (float)(end_pts - start_pts) / movie.video_track.settings().timescale << "s)" << endl;
//    std::stringstream s_dst_chunk; s_dst_chunk << s_dst.str() << "/" << index << ".mp4";
//    const string abs_dst_chunk = vireo::common::Path::MakeAbsolute(s_dst_chunk.str());
//    util::save(abs_dst_chunk, (*mp4_encoder)());
//  };
//
//  // get
//  vector<uint32_t> gop_boundaries;
//  for (uint32_t i = 0; i < movie.video_track.count(); ++i) {
//    if (movie.video_track(i).keyframe) {
//      gop_boundaries.push_back(i);
//    }
//  }
//  gop_boundaries.push_back(movie.video_track.count());
//
//  uint32_t chunk_index = 0;
//  for (auto it = gop_boundaries.begin(); it != gop_boundaries.end() - 1; ++it ) {
//    auto next = it + 1;
//    uint32_t start_idx = *it;
//    uint32_t end_idx = (*next) - 1;
//    uint64_t start_pts = movie.video_track(start_idx).pts;
//    uint64_t end_pts = movie.video_track(end_idx).pts;
//    auto video_track = movie.video_track.filter_index([start_idx, end_idx](uint32_t index) { return (index >= start_idx && index <= end_idx); });
//    mp4_encoder.reset(new mux::MP4(functional::Video<encode::Sample>(video_track, encode::Sample::Convert)));
//    write_chunk(chunk_index, start_pts, end_pts);
//    ++chunk_index;
//  }
//}
//if (movie.audio_track.count()) {  // Audio
//  mux::MP4 mp4_encoder(functional::Audio<encode::Sample>(movie.audio_track, encode::Sample::Convert), functional::Video<encode::Sample>());
//  cout << "audio.m4a (duration: " << (float)movie.audio_track.duration() / movie.audio_track.settings().timescale << "s)" << endl;
//  std::stringstream s_dst_chunk; s_dst_chunk << s_dst.str() << "/audio.m4a";
//  const string abs_dst_chunk = vireo::common::Path::MakeAbsolute(s_dst_chunk.str());
//  util::save(abs_dst_chunk, mp4_encoder());
//}
//
