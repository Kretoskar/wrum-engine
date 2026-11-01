#include "PCH.h"
#include "WrumCore/Rendering/DebugRenderer.h"

#include <cmath>
#include "WrumCore/Math/MathCore.h"

namespace Wrum
{
     bool DebugRenderer::Init(ArenaAllocator& arena)
     {
          _lifetimesLeft.reserve(MAX_LINE_COUNT);
          
          _shader = ArenaAllocator::New<Shader>(arena, "shaders/debug.vert", "shaders/vertexColor.frag");
          _shader->Bind();
          
          _lineVao = ArenaAllocator::New<VertexArrayObject>(arena);
          _lineVao->Bind();
          _lineVbo = ArenaAllocator::New<VertexBufferObject>(arena, (float*)_lineVertices, MAX_LINE_COUNT * 6 * 4);
          _lineEbo = ArenaAllocator::New<ElementBufferObject>(arena, _lineIndices, MAX_LINE_COUNT * 2 * 4);
          
          DrawNet(100, 1.0f, 100.0f, Vec3(0.6f, 0.6f, 0.6f));
          DrawNet(1000, 0.1f, 100.0f, Vec3(0.3f, 0.3f, 0.3f));

          //DrawCoordinateSystem();
          
          return true;
     }

     void DebugRenderer::Update(float deltaTime)
     {
          for (u32 i = 0; i < _lifetimesLeft.size(); i++)
          {
               DebugVertexLifetime& lifetime = _lifetimesLeft[i];
               lifetime.TimeLeft -= deltaTime;

               if (lifetime.TimeLeft <= 0)
               {
                    u32 index = lifetime.Index;
                    
                    _lineVertices[index] = _lineVertices[(_lineCount - 1) * 2];
                    _lineVertices[index + 1] = _lineVertices[(_lineCount - 1) * 2 - 1];

                    _lineVertices[(_lineCount - 1) * 2] = {};
                    _lineVertices[(_lineCount - 1) * 2 - 1] = {};

                    _lineIndices[index] = _lineIndices[(_lineCount - 1) * 2];
                    _lineIndices[index + 1] = _lineIndices[(_lineCount - 1) * 2 - 1];

                    _lineIndices[(_lineCount - 1) * 2] = {};
                    _lineIndices[(_lineCount - 1) * 2 - 1] = {};
                    
                    _lineCount--;
                    
                    _lifetimesLeft.erase(_lifetimesLeft.begin() + i);
               }
          }
     }

     void DebugRenderer::Render(const Camera& camera)
     {
          const u32 persistentLineCount = _lineCount;
          for (const LightBulbGizmo& gizmo : _lightBulbs)
          {
               DrawLightBulbLines(camera, gizmo);
          }

          _lineVao->Bind();
          _lineVbo->Init((float*)_lineVertices, _lineCount * 2 * 6 * 4);
          _lineEbo->Init(_lineIndices, MAX_LINE_COUNT * 2 * 4);
          // position
          _lineVao->LinkAttrib(*_lineVbo, 0, 3, GL_FLOAT, 6 * sizeof(float), (void*)0);
          // color
          _lineVao->LinkAttrib(*_lineVbo, 1, 3, GL_FLOAT, 6 * sizeof(float), (void*)(3 * sizeof(float)));
          
          _shader->Bind();
          _shader->SetModelMatrix(Mat4());
          _shader->SetVPMatrix(camera.GetVPMatrix());
          _lineVao->Bind();
          glDrawElements(GL_LINES, _lineCount * 2, GL_UNSIGNED_INT, 0);

          _lineCount = persistentLineCount;
          _lightBulbs.clear();
     }

     void DebugRenderer::DrawLightBulb(Vec3 position, Vec3 color, float size)
     {
          if (size > 0.0f)
          {
               _lightBulbs.push_back({position, color, size});
          }
     }

     void DebugRenderer::DrawLightBulbLines(const Camera& camera, const LightBulbGizmo& gizmo)
     {
          constexpr i32 arcSegments = 16;
          constexpr i32 rayCount = 7;
          constexpr i32 lineCount = arcSegments + rayCount + 10;
          if (_lineCount + lineCount > MAX_LINE_COUNT)
          {
               return;
          }

          const Vec3 right = camera.GetRightVector();
          const Vec3 up = Vec3::Cross(right, camera.Forward).Normalized();
          auto point = [&](float x, float y)
          {
               return gizmo.Position + right * (x * gizmo.Size) + up * (y * gizmo.Size);
          };
          auto line = [&](float x0, float y0, float x1, float y1)
          {
               DrawLine(point(x0, y0), point(x1, y1), gizmo.Color);
          };

          for (i32 i = 0; i < arcSegments; i++)
          {
               const f32 a0 = -MathCore::PI / 4.0f + 1.5f * MathCore::PI * i / arcSegments;
               const f32 a1 = -MathCore::PI / 4.0f + 1.5f * MathCore::PI * (i + 1) / arcSegments;
               line(std::cos(a0), std::sin(a0), std::cos(a1), std::sin(a1));
          }

          const f32 shoulder = std::sqrt(0.5f);
          line(-shoulder, -shoulder, -0.35f, -1.1f);
          line(shoulder, -shoulder, 0.35f, -1.1f);
          line(-0.35f, -1.1f, -0.35f, -1.55f);
          line(0.35f, -1.1f, 0.35f, -1.55f);
          line(-0.35f, -1.55f, 0.35f, -1.55f);
          line(-0.35f, -1.2f, 0.35f, -1.2f);
          line(-0.35f, -1.35f, 0.35f, -1.35f);
          line(-0.25f, -0.15f, -0.15f, -0.6f);
          line(-0.15f, -0.6f, 0.15f, -0.6f);
          line(0.15f, -0.6f, 0.25f, -0.15f);

          for (int i = 0; i < rayCount; i++)
          {
               const f32 angle = -MathCore::PI / 6.0f + (4.0f * MathCore::PI / 3.0f) * i / (rayCount - 1);
               const f32 x = std::cos(angle);
               const f32 y = std::sin(angle);
               line(x * 1.3f, y * 1.3f, x * 1.6f, y * 1.6f);
          }
     }

     void DebugRenderer::DrawLine(Vec3 start, Vec3 end, Vec3 color)
     {
          if (_lineCount == MAX_LINE_COUNT)
          {
               LOG_ERROR("Exceeded maximum debug line count of %d Can't draw any more lines", MAX_LINE_COUNT)
               return;
          }

          _lineVertices[_lineCount * 2] = { start, color };
          _lineVertices[_lineCount * 2 + 1] = { end, color };

          _lineIndices[_lineCount * 2] = _lineCount * 2;
          _lineIndices[_lineCount * 2 + 1] = _lineCount * 2 + 1;

          _lineCount++;
     }

     void DebugRenderer::DrawLine(Vec3 start, Vec3 end, Vec3 color, float lifetime, TimeUnit timeUnit)
     {
          _lifetimesLeft.emplace_back(_lineCount * 2,  Time::Convert(lifetime, timeUnit, TimeUnit::Milliseconds));
          
          DrawLine(start, end, color);
     }

     void DebugRenderer::DrawNet(unsigned count, float stride, float size, Vec3 color)
     {
          //TODO: Allow adding lines in batch
          for (int i = 0; i <= count; i++)
          {
               DrawLine(Vec3(size / 2, 0.0f, i * stride - count * stride / 2), Vec3(-size / 2, 0.0f, i * stride - count * stride / 2), color);
               DrawLine(Vec3(i * stride - count * stride / 2, 0.0f, size / 2), Vec3(i * stride - count * stride / 2, 0.0f, -size / 2), color);
          }
     }

     void DebugRenderer::DrawCoordinateSystem()
     {
          DrawLine({ 0,0,0 }, { 1.0f,0,0 }, { 1.0f,0,0 });
          DrawLine({ 1.0f,0,0 }, { 0.9f,0,-0.1f }, { 1.0f,0,0 });
          DrawLine({ 1.0f,0,0 }, { 0.9f,0,0.1f }, { 1.0f,0,0 });

          DrawLine({ 0,0,0 }, { 0,1.0f,0 }, { 0,1.0f,0 });
          DrawLine({ 0,1.0f,0 }, { 0,0.9f,0.1f }, { 0,1.0f,0 });
          DrawLine({ 0,1.0f,0 }, { 0,0.9f,-0.1f }, { 0,1.0f,0 });

          DrawLine({ 0,0,0 }, { 0,0,1.0f }, { 0,0,1.0f });
          DrawLine({ 0,0,1.0f }, { 0.1f,0,0.9f }, { 0,0,1.0f });
          DrawLine({ 0,0,1.0f }, { -0.1f,0,0.9f }, { 0,0,1.0f });
     }
}
