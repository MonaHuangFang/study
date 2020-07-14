//
//  mian.cpp
//  OpenGL_01
//
//  Created by 黄方 on 2020/6/30.
//  Copyright © 2020 黄方. All rights reserved.
//

#include <stdio.h>
#include "GLTools.h"
#include <GLUT/GLUT.h>

//工具类
GLBatch triangleBatch;

//定义着色管理器
GLShaderManager shaderManager;

//设置正方形参赛
GLfloat blockSize = 0.1f;

GLfloat vVerts[] = {
   -blockSize,-blockSize,0.0f,
    blockSize,-blockSize,0.0f,
    blockSize,blockSize,0.0f,
    -blockSize,blockSize,0.0f
};

GLfloat xPos = 0.0;
GLfloat yPos = 0.0;

void ChangeSize(int w, int h){
    //改变窗口大小
    glViewport(0, 0, w, h);
}

//确定顶点数据
void SetupRC(){
    //设置背景颜色
    glClearColor(0.98f, 0.4f, 0.7f, 1.0f);
    
    //初始化着色管理器
    shaderManager.InitializeStockShaders();
    
//    //设置三角形顶点数组
//    GLfloat vVerts[] = {
//        -0.5f,0.0f,0.0f,
//        0.5f,0.0f,0.0f,
//        0.0f,0.5f,0.0f,
//    };
//
//    triangleBatch.Begin(GL_TRIANGLES, 3);
    
    //设置正方形
    triangleBatch.Begin(GL_TRIANGLE_FAN, 4);
    triangleBatch.CopyVertexData3f(vVerts);
    triangleBatch.End();
}

void SpecialKeys(int key, int x, int y){
    GLfloat stepSize = 0.025f;

    
    if(key == GLUT_KEY_UP){
        yPos += stepSize;
    }else if (key == GLUT_KEY_DOWN){
        yPos -= stepSize;
    }else if (key == GLUT_KEY_LEFT){
        xPos -= stepSize;
    }else if (key == GLUT_KEY_RIGHT){
        xPos += stepSize;
    }
    
    if(xPos < -1.0 + blockSize){
        x = -0.1 + blockSize;
    }
    if(xPos > 1.0 - blockSize){
        xPos = 1.0 - blockSize;
    }
    if(yPos < -1.0 + blockSize){
        yPos = -1.0 + blockSize;
    }
    if (yPos > 1.0 - blockSize) {
        yPos = 1.0 + blockSize;
    }
    
    glutPostRedisplay();
}

//开始渲染
void RenderScene(){
    //清除一个或一组特定的缓冲区
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT|GL_STENCIL_BUFFER_BIT);
    GLfloat vRed[] = {0.0f,1.0f,0.0f,1.0f};
    
    //矩阵
    M3DMatrix44f mTransf;
    
    //平移矩阵
    m3dTranslationMatrix44(mTransf, xPos, yPos, 0.0);
    
    //平面着色器
    shaderManager.UseStockShader(GLT_SHADER_FLAT, mTransf, vRed);
    
    //提交着色器
    triangleBatch.Draw();
    
    //将在后台缓冲区进行渲染，然后在结束时提交到前台
    glutSwapBuffers();
}

int main(int argc, char *argv[]){
    //设置当前工作目录，针对MAC OS X
    gltSetWorkingDirectory(argv[0]);
    
    //初始化GLUT库
    glutInit(&argc, argv);
    
    //初始化双缓冲窗口，GLUT_DOUBLE̵、GLUT_RGBA̵、GLUT_DEPTH̵、GLUT_STENCIL分别指双缓冲窗口、RGBA颜色模式、深度测试、模版缓冲区
    glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGBA|GLUT_DEPTH|GLUT_STENCIL);
    
    //设置窗口大小，标题窗口
    glutInitWindowSize(500, 500);
    
    glutCreateWindow("Triangle");
    
    //注册回调函数
    glutReshapeFunc(ChangeSize);
    
    //注册显示函数
    glutDisplayFunc(RenderScene);
    
    //注册特殊函数
    glutSpecialFunc(SpecialKeys);
    
    GLenum err = glewInit();
    
    if(GLEW_OK != err){
        fprintf(stderr, "glew error : %s\n",glewGetErrorString(err));
        return 1;
    }
    
    //设置渲染环境
    SetupRC();
    
    glutMainLoop();
    
    return 0;
}
