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
GLfloat blockSize = 0.2f;

GLfloat vVerts[] = {
   -blockSize,-blockSize,0.0f,
    blockSize,-blockSize,0.0f,
    blockSize,blockSize,0.0f,
    -blockSize,blockSize,0.0f
};

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
    GLfloat blockX = vVerts[0];
    GLfloat blockY = vVerts[10];
    
    printf("v[0] = %f\n",blockX);
    printf("v[10] = %f\n",blockY);
    
    if(key == GLUT_KEY_UP){
        blockY += stepSize;
    }else if (key == GLUT_KEY_DOWN){
        blockY -= stepSize;
    }else if (key == GLUT_KEY_LEFT){
        blockX -= stepSize;
    }else if (key == GLUT_KEY_RIGHT){
        blockX += stepSize;
    }
    
    if (blockX < -1.0f) {
        blockX = -1.0f;
    }
    
    if (blockX > (1.0 - blockSize * 2)) {
        blockX = 1.0f - blockSize * 2;
    }
    
    if (blockY < -1.0f + blockSize * 2 ) {
        blockY = -1.0f + blockSize * 2;
    }
    
    if (blockY > 1.0f) {
        blockY = 1.0f;
    }
    
    printf("blockX = %f\n",blockX);
    printf("blockY = %f\n",blockY);
    
    vVerts[0] = blockX;
    vVerts[1] = blockY - blockSize*2;
    printf("(%f,%f)\n",vVerts[0],vVerts[1]);
    
    vVerts[3] = blockX + blockSize*2;
    vVerts[4] = blockY - blockSize*2;
    printf("(%f,%f)\n",vVerts[3],vVerts[4]);
    
    vVerts[6] = blockX + blockSize*2;
    vVerts[7] = blockY;
    printf("(%f,%f)\n",vVerts[6],vVerts[7]);
    
    vVerts[9] = blockX;
    vVerts[10] = blockY;
    printf("(%f,%f)\n",vVerts[9],vVerts[10]);
    
    triangleBatch.CopyVertexData3f(vVerts);
    glutPostRedisplay();
}

//开始渲染
void RenderScene(){
    //清除一个或一组特定的缓冲区
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT|GL_STENCIL_BUFFER_BIT);
    
    //设置一组浮点数来表示红色
    GLfloat vRed[] = {1.0f,0.0f,0.0f,1.0f};
    
    //传递到存储着色器，即GLT_SHADER_IDENTITY着色器，这个着色器只是使用指定颜色以默认笛卡尔坐标在屏幕上渲染几何图形
    shaderManager.UseStockShader(GLT_SHADER_IDENTITY,vRed);
    
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
