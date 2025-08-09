#include "PCH.h"
#include "WrumCore/Rendering/DebugRenderer.h"

namespace Wrum
{
     bool DebugRenderer::Init()
     {
          _lifetimesLeft.reserve(MAX_LINE_COUNT);
          
          _shader = ArenaAllocator::New<Shader>(_arena, "shaders/debug.vert", "shaders/debug.frag");
          _shader->Bind();
          
          _lineVao = ArenaAllocator::New<VertexArrayObject>(_arena);
          _lineVao->Bind();
          _lineVbo = ArenaAllocator::New<VertexBufferObject>(_arena, (float*)_lineVertices, MAX_LINE_COUNT * 6 * 4);
          _lineEbo = ArenaAllocator::New<ElementBufferObject>(_arena, _lineIndices, MAX_LINE_COUNT * 2 * 4);
          
          AddNet(1000, 0.1f, 100.0f, Vec3(0.3f, 0.3f, 0.3f));
          AddNet(100, 1.0f, 100.0f, Vec3(0.6f, 0.6f, 0.6f));
          
          //AddLine({ 0,0,0 }, { 1.0f,0,0 }, { 1.0f,0,0 });
          //AddLine({ 1.0f,0,0 }, { 0.9f,0,-0.1f }, { 1.0f,0,0 });
          //AddLine({ 1.0f,0,0 }, { 0.9f,0,0.1f }, { 1.0f,0,0 });
//
          //AddLine({ 0,0,0 }, { 0,1.0f,0 }, { 0,1.0f,0 });
          //AddLine({ 0,1.0f,0 }, { 0,0.9f,0.1f }, { 0,1.0f,0 });
          //AddLine({ 0,1.0f,0 }, { 0,0.9f,-0.1f }, { 0,1.0f,0 });
//
          //AddLine({ 0,0,0 }, { 0,0,1.0f }, { 0,0,1.0f });
          //AddLine({ 0,0,1.0f }, { 0.1f,0,0.9f }, { 0,0,1.0f });
          AddLine({ 0,0,1.0f }, { -0.1f,0,0.9f }, { 0,0,1.0f }, 5000.0f);

          
          
          return true;
     }

     void DebugRenderer::Update(float deltaTime)
     {
          for (uint32 i = 0; i < _lifetimesLeft.size(); i++)
          {
               DebugVertexLifetime& lifetime = _lifetimesLeft[i];
               lifetime.TimeLeft -= deltaTime;

               if (lifetime.TimeLeft <= 0)
               {
                    uint32 index = lifetime.Index;
                    
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
     }

     void DebugRenderer::AddLine(Vec3 start, Vec3 end, Vec3 color)
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

     void DebugRenderer::AddLine(Vec3 start, Vec3 end, Vec3 color, float lifetime)
     {
          _lifetimesLeft.emplace_back(_lineCount * 2, lifetime);
          
          AddLine(start, end, color);
     }

     void DebugRenderer::AddNet(unsigned count, float stride, float size, Vec3 color)
     {
          //TODO: Allow adding lines in batch
          for (int i = 0; i <= count; i++)
          {
               AddLine(Vec3(size / 2, 0.0f, i * stride - count * stride / 2), Vec3(-size / 2, 0.0f, i * stride - count * stride / 2), color);
               AddLine(Vec3(i * stride - count * stride / 2, 0.0f, size / 2), Vec3(i * stride - count * stride / 2, 0.0f, -size / 2), color);
          }
     }
}
