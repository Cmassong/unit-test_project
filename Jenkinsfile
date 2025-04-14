pipeline {
    agent any

    stages {
        stage('Checkout') {
            steps {
                checkout scm
            }
        }

        stage('Clean') {
            steps {
                sh 'make clean'
            }
        }

        stage('Build and Run Tests') {
            steps {
                sh 'make test'
            }
        }

         stage('Build and Run program') {
            steps {
                sh 'make run'
            }
        }
    }

    post {
        always {
            archiveArtifacts artifacts: 'test_results.txt', allowEmptyArchive: true
        }

        success {
            githubNotify context: 'build', status: 'SUCCESS', description: 'Tests passed'
        }
        failure {
            githubNotify context: 'build', status: 'FAILURE', description: 'Tests failed'
        }


    }
}
