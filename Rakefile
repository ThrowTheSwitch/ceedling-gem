require "bundler"
Bundler::GemHelper.install_tasks
require "./lib/ceedling"
require "fileutils"
require "erb"

def update_revisions
  puts "Updating version info..."
  versions = {}
  full_version_info = nil
  Dir.chdir(Ceedling::NEW_PROJECT_DIR) { full_version_info = `rake version` }
  puts full_version_info
  full_version_info.each_line do |line|
    line = line.split("::")
    versions[line.first.strip.upcase] = line.last.strip
  end
  result = ERB.new(File.read("lib/ceedling/version.rb.erb")).result(binding)
  File.open("lib/ceedling/version.rb", "wb+") { |f| f.puts result }
end

desc "update all the tools from sourceforge and update version info"
task :update_tools do

  puts "\nRetrieving ceedling content from SourceForge..."
  rm_rf "temp"
  mkdir "temp"

  libs = [
    {:path => './vendor/unity'},
    {:path => './vendor/cmock'},
    {:path => './vendor/c_exception'},
    {:path => '.'}
  ]
  cd "temp" do
    sh 'svn co http://ceedling.svn.sourceforge.net/svnroot/ceedling/trunk .'
    libs.each do |lib|
      svn_info = `svn info #{lib[:path]}/`
      lib[:revision] = svn_info.split("\n")[4].match(/ (\d+)/)[1]
      revision_file = "#{lib[:path]}/release/build.info"
      puts "Recorded lib revision #{lib[:revision]} in #{revision_file}"
      File.open(revision_file, 'w'){|f| f.write lib[:revision]}
    end
    rm_rf Dir["./**/.svn/"], :verbose => false # remove svn artifacts
  end

  # define mapping for pruning content from sourceforge
  mapping = [
    {:src => 'lib/',                                             :dest => ''},
    {:src => 'plugins/',                                         :dest => ''},
    {:src => 'release/',                                         :dest => ''},
    {:src => 'vendor/c_exception/lib/',                          :dest => 'vendor/c_exception/'},
    {:src => 'vendor/c_exception/release/',                      :dest => 'vendor/c_exception/'},
    {:src => 'vendor/cmock/config/',                             :dest => 'vendor/cmock/'},
    {:src => 'vendor/cmock/lib/',                                :dest => 'vendor/cmock/'},
    {:src => 'vendor/cmock/release/',                            :dest => 'vendor/cmock/'},
    {:src => 'vendor/cmock/src/',                                :dest => 'vendor/cmock/'},
    {:src => 'vendor/constructor/lib/',                          :dest => 'vendor/constructor/'},
    {:src => 'vendor/deep_merge/lib/',                           :dest => 'vendor/deep_merge/'},
    {:src => 'vendor/diy/lib',                                   :dest => 'vendor/diy/'},
    {:src => 'vendor/unity/auto/',                               :dest => 'vendor/unity/'},
    {:src => 'vendor/unity/release/',                            :dest => 'vendor/unity/'},
    {:src => 'vendor/unity/src/',                                :dest => 'vendor/unity/'},
    {:src => 'vendor/c_exception/docs/CExceptionSummary.pdf',    :dest => 'docs/', :is_file => true},
    {:src => 'vendor/cmock/docs/CMock Summary.pdf',              :dest => 'docs/', :is_file => true},
    {:src => 'docs/CeedlingPacket.pdf',                          :dest => 'docs/', :is_file => true},
    {:src => 'vendor/unity/docs/Unity Summary.pdf',              :dest => 'docs/', :is_file => true},
  ]

  puts "\nUpdating tools with the latest goods..."
  rm_rf "new_project_template/vendor/**"
  mapping.each do |path|
    dest = "new_project_template/vendor/ceedling/#{path[:dest]}"
    dir = dest.sub(/\w+$/, '')
    if !File.exist?(dir)
      mkdir_p dest
    end
    puts "temp/#{path[:src]} -> #{dest}"
    FileUtils.cp_r "temp/#{path[:src]}", "#{dest}"
  end
  rm_rf "temp"
  update_revisions
end

desc "Update versions"
task :update_revs do
  update_revisions
end
