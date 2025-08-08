#include "PCH.h"
#include "WrumCore/Rendering/DebugRenderer.h"

namespace Wrum
{
     bool DebugRenderer::Init()
     {
          _shader = new Shader("shaders/debug.vert", "shaders/debug.frag");
          _shader->Bind();

          _lineVao = new VertexArrayObject();
          _lineVao->Bind();
          _lineVbo = new VertexBufferObject((float*)_lineVertices, MAX_LINE_COUNT * 6 * 4);
          _lineEbo = new ElementBufferObject(_lineIndices, MAX_LINE_COUNT * 2 * 4);

          DrawNet(1000, 0.1f, 100.0f, Vec3(0.3f, 0.3f, 0.3f));
          DrawNet(100, 1.0f, 100.0f, Vec3(0.6f, 0.6f, 0.6f));
		
          AddLine({ 0,0,0 }, { 1.0f,0,0 }, { 1.0f,0,0 });
          AddLine({ 1.0f,0,0 }, { 0.9f,0,-0.1f }, { 1.0f,0,0 });
          AddLine({ 1.0f,0,0 }, { 0.9f,0,0.1f }, { 1.0f,0,0 });

          AddLine({ 0,0,0 }, { 0,1.0f,0 }, { 0,1.0f,0 });
          AddLine({ 0,1.0f,0 }, { 0,0.9f,0.1f }, { 0,1.0f,0 });
          AddLine({ 0,1.0f,0 }, { 0,0.9f,-0.1f }, { 0,1.0f,0 });


          AddLine({ 0,0,0 }, { 0,0,1.0f }, { 0,0,1.0f });
          AddLine({ 0,0,1.0f }, { 0.1f,0,0.9f }, { 0,0,1.0f });
          AddLine({ 0,0,1.0f }, { -0.1f,0,0.9f }, { 0,0,1.0f });
	
          _lineVao->Bind();
          _lineVbo->Init((float*)_lineVertices, _lineCount * 2 * 6 * 4);
          _lineEbo->Init(_lineIndices, MAX_LINE_COUNT * 2 * 4);
          // position
          _lineVao->LinkAttrib(*_lineVbo, 0, 3, GL_FLOAT, 6 * sizeof(float), (void*)0);
          // color
          _lineVao->LinkAttrib(*_lineVbo, 1, 3, GL_FLOAT, 6 * sizeof(float), (void*)(3 * sizeof(float)));
          
          return true;
     }

     void DebugRenderer::Render(const Camera& camera)
     {
          _shader->Bind();
          _shader->SetModelMatrix(Mat4());
          _shader->SetVPMatrix(camera.GetVPMatrix());
          _lineVao->Bind();
          glDrawElements(GL_LINES, sizeof(_lineIndices) / sizeof(int), GL_UNSIGNED_INT, 0);
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

     void DebugRenderer::DrawNet(unsigned count, float stride, float size, Vec3 color)
     {
          //TODO: Allow adding lines in batch
          for (int i = 0; i <= count; i++)
          {
               AddLine(Vec3(size / 2, 0.0f, i * stride - count * stride / 2), Vec3(-size / 2, 0.0f, i * stride - count * stride / 2), color);
               AddLine(Vec3(i * stride - count * stride / 2, 0.0f, size / 2), Vec3(i * stride - count * stride / 2, 0.0f, -size / 2), color);
          }
     }
}
