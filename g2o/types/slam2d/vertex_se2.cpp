// g2o - General Graph Optimization
// Copyright (C) 2011 R. Kuemmerle, G. Grisetti, W. Burgard
// All rights reserved.
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are
// met:
//
// * Redistributions of source code must retain the above copyright notice,
//   this list of conditions and the following disclaimer.
// * Redistributions in binary form must reproduce the above copyright
//   notice, this list of conditions and the following disclaimer in the
//   documentation and/or other materials provided with the distribution.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS
// IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED
// TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A
// PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
// HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
// SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED
// TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
// PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
// LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
// NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
// SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

#include "vertex_se2.h"
#include <typeinfo>

#ifdef WINDOWS
#include <windows.h>
#endif

#ifdef G2O_HAVE_OPENGL
#ifdef __APPLE__
#include <OpenGL/gl.h>
#else
#include <GL/gl.h>
#endif
#endif

namespace g2o {

  VertexSE2::VertexSE2() :
    BaseVertex<3, SE2>()
  {
  }

  bool VertexSE2::read(std::istream& is)
  {
    Eigen::Vector3d p;
    is >> p[0] >> p[1] >> p[2];
    setEstimate(p);
    return true;
  }

  bool VertexSE2::write(std::ostream& os) const
  {
    Eigen::Vector3d p = estimate().toVector();
    os << p[0] << " " << p[1] << " " << p[2];
    return os.good();
  }

  VertexSE2WriteGnuplotAction::VertexSE2WriteGnuplotAction(): WriteGnuplotAction(typeid(VertexSE2).name()){}

  HyperGraphElementAction* VertexSE2WriteGnuplotAction::operator()(HyperGraph::HyperGraphElement* element, HyperGraphElementAction::Parameters* params_){
    if (typeid(*element).name()!=_typeName)
      return 0;
    WriteGnuplotAction::Parameters* params=static_cast<WriteGnuplotAction::Parameters*>(params_);
    if (!params || !params->os){
      std::cerr << __PRETTY_FUNCTION__ << ": warning, no valid output stream specified" << std::endl;
      return 0;
    }
    
    VertexSE2* v =  static_cast<VertexSE2*>(element);
    *(params->os) << v->estimate().translation().x() << " " << v->estimate().translation().y()
      << " " << v->estimate().rotation().angle() << std::endl;
    return this;
  }

#ifdef G2O_HAVE_OPENGL
  VertexSE2DrawAction::VertexSE2DrawAction(): DrawAction(typeid(VertexSE2).name()){
    _drawActions = 0;
  }

  HyperGraphElementAction* VertexSE2DrawAction::operator()(HyperGraph::HyperGraphElement* element, 
                 HyperGraphElementAction::Parameters* params_){
    if (typeid(*element).name()!=_typeName)
      return 0;

    if (! _drawActions){
      _drawActions = HyperGraphActionLibrary::instance()->actionByName("draw");
    }

    VertexSE2* that = static_cast<VertexSE2*>(element);
    glColor3f(0.5,0.5,0.8);
    glPushAttrib(GL_ENABLE_BIT);
    glDisable(GL_LIGHTING);
    glPushMatrix();
    glTranslatef(that->estimate().translation().x(),that->estimate().translation().y(),0.);
    glRotatef(RAD2DEG(that->estimate().rotation().angle()),0.,0.,1.);
    glBegin(GL_TRIANGLE_FAN);
    glVertex3f( 0.1 ,0.  ,0.);
    glVertex3f(-0.1 ,-0.05, 0.);
    glVertex3f(-0.1 , 0.05, 0.);
    glEnd();
    if (that->userData() && _drawActions )
      (*_drawActions)(that->userData(), params_);
    glPopMatrix();
    glPopAttrib();
    return this;
  }
#endif


} // end namespace
