#include "vireo/base_h.h"
#include "vireo/base_cpp.h"
#include "vireo/demux/movie.h"
#include "vireo/mux/mp4.h"
#include "vireo/util/util.h"

#include "lib.h"
#include "crow_all.h"

using namespace std;

bool is_request_valid(const crow::request& req) {
  return req.url_params.get("bitrate") != nullptr &&
    req.url_params.get("width") != nullptr && 
    req.url_params.get("height") != nullptr;
}

stringstream extract(VideoChunkInfo chunk_info) {
  stringstream chunk;

  vireo::demux::Movie movie(chunk_info.filename);
  if (movie.video_track.count()) {
    unique_ptr<vireo::mux::MP4> mp4_encoder;

    vector<uint32_t> gop_boundaries;
    for (uint32_t i = 0; i < movie.video_track.count(); ++i) {
      if (movie.video_track(i).keyframe) {
        gop_boundaries.push_back(i);
      }
    }
    gop_boundaries.push_back(movie.video_track.count());

    uint32_t chunk_index = 0;
    for (auto it = gop_boundaries.begin(); it != gop_boundaries.end() - 1; ++it ) {
      auto next = it + 1;
      uint32_t start_idx = *it;
      uint32_t end_idx = (*next) - 1;
      uint64_t start_pts = movie.video_track(start_idx).pts;
      uint64_t end_pts = movie.video_track(end_idx).pts;
      auto video_track = movie.video_track.filter_index([start_idx, end_idx](uint32_t index) { return (index >= start_idx && index <= end_idx); });
      mp4_encoder.reset(new vireo::mux::MP4(vireo::functional::Video<vireo::encode::Sample>(video_track, vireo::encode::Sample::Convert)));
//      write_chunk(chunk_index, start_pts, end_pts);
      ++chunk_index;
    }
  }

  return chunk;
}

stringstream transcode(stringstream* chunk) {
  stringstream transcoded_chunk;
  transcoded_chunk << "transcoded chunk here";
  return transcoded_chunk;
}


