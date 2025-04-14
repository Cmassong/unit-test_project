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
    }

    post {
        always {
            archiveArtifacts artifacts: 'test_results.txt', allowEmptyArchive: true
        }

        success {
            setGitHubPullRequestStatus context: 'Jenkins', message: 'Test success', state: 'SUCCESS'
        }
        failure {
            setGitHubPullRequestStatus context: 'Jenkins', message: 'Test failed', state: 'FAILURE'
        }


    }
}
